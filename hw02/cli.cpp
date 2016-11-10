#include "cli.hpp"
#include "die.hpp"
#include <cstring>
#include <fstream>
#include <sstream>

void OptionVal::set(const std::string& val) {
  assert(!_intValue);
  _stringValue = val;
}

void OptionVal::set(intmax_t val) {
  assert(_stringValue.empty());
  _intValue = val;
}

ParseOutcome Option::parse(const std::string& v) {
  if (_value.valid() && _accum == A_AssertSingle)
    return PO_NoMoreArgumentsExpected;
  if (_value.valid() && _accum == A_KeepLast)
    _value.clear();

  if (_type == OT_Int) {
    char* end;
    intmax_t intval = std::strtoll(v.c_str(), &end, 0);
    if (end == v ||
        *end != '\0')  // nothing was read or ended at non-null character
      return PO_InvalidFormat;
    if (_accum == A_KeepLast || !_value.valid())
      _value.set(intval);
    // if _accum == A_KeepFirst and there is already some value we do nothing
  } else if (_accum == A_KeepLast || !_value.valid())
    _value.set(v);
  return PO_Success;
}

void Option::dump() const {
  if (!hasValue())
    return;
  std::cout << "-" << _shortName << " / --" << _longName << ": ";
  switch (_type) {
    case OT_String:
      std::cout << getString();
      break;
    case OT_Int:
      std::cout << getInt();
      break;
  }
  std::cout << std::endl;
}

Option* Parser::add(char shortName,
                    const std::string& longName,
                    const std::string& help,
                    OptionType ty) {
  _options.push_back(std::make_unique<Option>(shortName, longName, help, ty));
  Option* opt = (*(_options.end() - 1)).get();
  _shortMap[opt->shortName()] = opt;
  _longMap[opt->longName()] = opt;
  return opt;
}

/*
Parser::~Parser() {
        for (std::vector<Option *>::iterator it = _options.begin();
             it != _options.end(); ++it)
                delete *it;
}*/

void Parser::clear() {
  for (std::unique_ptr<Option>& option : _options) {
    option->clear();
  }
  /*
for (std::vector<Option *>::iterator it = _options.begin();
     it != _options.end(); ++it)
        (*it)->clear();*/
}

void Parser::dump() const {
  for (const std::unique_ptr<Option>& option : _options) {
    option->dump();
  }
  /*
for (std::vector<Option *>::const_iterator it = _options.begin();
     it != _options.end(); ++it)
        (*it)->dump();
 */
  std::cout << std::endl << "extras: ";
  for (const std::string& extra : _extra) {
    std::cout << extra << ", ";
  }
  /*std::copy(_extra.begin(), _extra.end(),
    std::ostream_iterator<const char *>(std::cout, ", "));*/
  std::cout << std::endl;
}

void Parser::fail(const std::string& msg) const {
  std::stringstream ss;
  ss << "Commandline parser error: " << msg << std::endl;
  help(ss);
  die(ss.str());
}

void Parser::help(std::ostream& os) const {
  for (const std::unique_ptr<Option>& option : _options) {
    Option* opt = option.get();
    os << "\t-" << opt->shortName() << ", --" << opt->longName() << std::endl
       << "\t\t" << opt->help() << std::endl
       << std::endl;
  }
  /*
for (std::vector<std::unique_ptr<Option>>::iterator it = _options.begin();
     it != _options.end(); ++it) {
        Option *opt = it->get();
        os << "\t-" << opt->shortName() << ", --" << opt->longName() <<
std::endl
           << "\t\t" << opt->help() << std::endl
           << std::endl;
}*/
}

std::map<std::string, Option*>::iterator Parser::shortCmdFind(
    const std::string& substring) {
  std::map<std::string, Option*>::iterator found;
  int possibleOptions = 0;
  for (std::map<std::string, Option*>::iterator it = _longMap.begin();
       it != _longMap.end(); it++) {
    if (it->first.find(substring) == 0) {
      found = it;
      possibleOptions++;
    }
  }
  if (possibleOptions == 1)
    return found;
  if (possibleOptions > 1)
    die("Ambiguos option!");
  return _longMap.end();
};

void Parser::parse(const char* const* argv) {
  // clear();
  // for (; argc; --argc, ++argv) {
  while (*argv != nullptr) {
    bool charCmd = false;
    const char* arg = *argv;
    if (arg[0] == '-') {
      // find option
      Option* opt = nullptr;
      if (arg[1] == '-') {
        std::map<std::string, Option*>::iterator it = _longMap.find(arg + 2);
        if (it == _longMap.end()) {  // does not find
          it = shortCmdFind(arg + 2);
          if (it == _longMap.end()) {
            return fail(std::string("Unknown long option ") + arg);
          }
        }
        opt = it->second;
      } else {
        std::map<char, Option*>::iterator it = _shortMap.find(arg[1]);
        if (it == _shortMap.end())
          return fail(std::string("Unknown short option ") + arg);
        opt = it->second;
        charCmd = true;
      }
      assert(opt);
      // parse value
      if (opt->needsParameter()) {
        std::string argument;
        if (*(argv + 1) == nullptr) {
          die("Missing parameter!");
        }
        if (charCmd && std::strlen(argv[0]) > 2) {
          argument = (*argv + 2);
          ++argv;
        } else {
          //--argc;
          ++argv;
          argument = argv[0];
        }
        // assert(argc);
        switch (opt->parse(argument)) {
          case PO_NoMoreArgumentsExpected:
            return fail(std::string("More than one argument given for ") + arg +
                        " but only one expected");
          case PO_InvalidFormat:
            return fail(std::string("Could not parse value ") + *argv +
                        " for " + arg);
          case PO_Success:
            break;
        }
        argv++;
      } else {
        opt->parse(opt->longName());
        argv++;
      }
    } else {
      _extra.push_back(arg);
      return;
    }
  }
}

void FileCommandsParser::fail(const std::string& msg) const {
  std::stringstream ss;
  ss << "Commandline parser error: " << msg << std::endl;
  help(ss);
  die(ss.str());
}

void FileCommandsParser::help(std::ostream& os) const {
  os << "Usage: <input_file> <output_file> <command> [<command options>...]"
     << std::endl
     << std::endl;
  for (const std::pair<const std::string, std::unique_ptr<Parser> >& pair :
       _subcommands) {
    os << pair.first << ":" << std::endl;
    pair.second->help(os);
    os << std::endl;
  }
  /*
for (std::map<std::string, std::unique_ptr<Parser>>::iterator it =
_subcommands.begin();
     it != _subcommands.end(); ++it) {
        os << it->first << ":" << std::endl;
        it->second->help(os);
        os << std::endl;
}
 */
}

static bool fileExists(const std::string& file) {
  std::fstream checkFile(file);
  return checkFile.good();
  // std::fstream *fs = new std::fstream(file.c_str());
  // return fs->good();
}

Parser* FileCommandsParser::parse(int argc, const char* const* argv) {
  if (argc < 3)
    fail("at least input and output file and command expected");

  _in = argv[0];
  if (!fileExists(_in))
    fail("input file must exist");
  _out = argv[1];
  if (fileExists(_out)) {
    char choice;
    std::cout << "Output file exists, do you wish to override it? [y/N]";
    std::cin >> choice;
    if (choice != 'y')
      return nullptr;
  }

  std::map<const std::string, std::unique_ptr<Parser> >::iterator cmd =
      _subcommands.find(argv[2]);
  if (cmd == _subcommands.end())
    fail(std::string("Unknown command ") + argv[2]);
  // argc -= 3;
  argv += 3;
  cmd->second->parse(argv);
  return cmd->second.get();
}
