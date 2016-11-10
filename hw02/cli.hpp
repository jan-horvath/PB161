#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#ifndef CLI_HPP
#define CLI_HPP

// type of parsed parameter
// **numeric value and meaning of the existing values and the name of type
// should not be changed**
enum OptionType { OT_String, OT_Int };

// a way to accumulate arguments if passed multiple times from commandline
enum Accumulate { A_KeepFirst, A_KeepLast, A_AssertSingle };

// Holds value of parameter but contains no parsing functionality
struct OptionVal {
  OptionVal() : _stringValue(""), _intValue(0) {}
  //~OptionVal() {}

  void set(const std::string& val);
  void set(intmax_t val);

  void clear() {
    _intValue = 0;
    _stringValue = "";
  }

  bool valid() const {
    assert(_intValue == 0 || _stringValue.empty());
    return !_stringValue.empty() || _intValue != 0;
  }

  intmax_t getInt() const {
    assert(_intValue);
    return _intValue;
  }

  const std::string& getString() const {
    assert(!_stringValue.empty());
    return _stringValue;
  }

 private:
  std::string _stringValue;
  intmax_t _intValue;
};

// result of parse in option
// **numeric value and meaning of the existing values and the name of type
// should not be changed**
enum ParseOutcome { PO_Success, PO_InvalidFormat, PO_NoMoreArgumentsExpected };

// Represents option, including its name, description, and parsing support and
// parsed value
// **interface should respect requirements given in the assignment**
struct Option {
  // ADD ACCUMULATE
  Option(char shortName,
         const std::string& longName,
         const std::string& help,
         OptionType ty = OT_String)
      : _longName(longName),
        _shortName(shortName),
        _help(help),
        _type(ty),
        _accum(A_AssertSingle),
        _needsParameter(true) {}

  ParseOutcome parse(const std::string& v);

  void clear() { _value.clear(); }

  bool hasValue() const { return _value.valid(); }

  const std::string& longName() const { return _longName; }
  char shortName() const { return _shortName; }
  const std::string& help() const { return _help; }

  const std::string& getString() const { return _value.getString(); }
  intmax_t getInt() const { return _value.getInt(); }

  bool needsParameter() { return _needsParameter; }
  void setNeedsParameter(bool x) { _needsParameter = x; }

  void dump() const;

 private:
  const std::string _longName;
  char _shortName;
  const std::string _help;
  OptionVal _value;
  OptionType _type;
  Accumulate _accum;
  bool _needsParameter;
};

// basic parser of commandline options
// **interface should respect requirements given in the assignment**
struct Parser {
  //~Parser();

  Option* add(char shortName,
              const std::string& longName,
              const std::string& help,
              OptionType ty = OT_String);

  void fail(const std::string& msg) const;
  void dump() const;

  void clear();
  void help(std::ostream& os = std::cout) const;

  void parse(const char* const* argv);

  std::map<std::string, Option*>::iterator shortCmdFind(
      const std::string& substring);

  const std::vector<std::string>& extra() const { return _extra; }

  std::vector<std::string>& getExtra() { return _extra; }
  std::map<std::string, Option*>& getLongMap() { return _longMap; }
  std::map<char, Option*>& getShortMap() { return _shortMap; }

 private:
  std::vector<std::unique_ptr<Option> > _options;
  std::vector<std::string> _extra;
  std::map<std::string, Option*> _longMap;
  std::map<char, Option*> _shortMap;
};

// parser of commandline with subnocommands (represented by Parser)
struct FileCommandsParser {
  // TODO: Return NULL when subcommand already present
  Parser* add(const std::string& name) {
    if (_subcommands.find(name) != _subcommands.end())
      return nullptr;
    return _subcommands.insert(std::make_pair(name, std::make_unique<Parser>()))
        .first->second.get();
  }

  void fail(const std::string& msg) const;
  void help(std::ostream& os = std::cout) const;
  Parser* parse(int argc, const char* const* argv);
  const std::map<const std::string, std::unique_ptr<Parser> >&
  getSubcommands() {
    return _subcommands;
  }

  const std::string& inputFile() const { return _in; }
  const std::string& outputFile() const { return _out; }

 private:
  std::map<const std::string, std::unique_ptr<Parser> > _subcommands;
  std::string _in;
  std::string _out;
};

#endif  // CLI_HPP
