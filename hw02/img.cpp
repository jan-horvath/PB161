#include "cli.hpp"
#include "die.hpp"
#include "tools.hpp"

// parse color from string, in form of r,g,b or r,g,b,a where all of r,g,b,a
// are numbers from 0 to 255 in decadic, ocatal (with leading 0) or hexadecimal
// (with leading 0x form)
bool parseColor(std::string color, Pixel& px) {
  int red, green, blue, alpha;
  std::string::size_type next = 0;
  try {
    red = std::stoi(color.c_str(), nullptr, 0);
    next = color.find(',') + 1;
    green = std::stoi(color.c_str() + next, nullptr, 0);
    next = color.find(',', next) + 1;
    blue = std::stoi(color.c_str() + next, nullptr, 0);
    next = color.find(',', next) + 1;
  } catch (const std::exception& e) {
    die("Invalid color input!");
  }

  if (next == std::string::npos + 1)
    alpha = 255;
  else
    alpha = std::stoi(color.c_str() + next, nullptr, 0);
  if ((red > 255) || (green > 255) || (blue > 255) || (alpha > 255) ||
      (red < 0) || (green < 0) || (blue < 0) || (alpha < 0)) {
    die("Invalid color/alpha options.");
  }
  px.r = red;
  px.g = green;
  px.b = blue;
  px.a = alpha;
  return true;
}

// entry point of the program
// **function header should not be modified**
int img(int argc, const char* const* argv) {
  FileCommandsParser fcp;
  Parser *s_grayscale = fcp.add("grayscale"), *s_cut = fcp.add("cut"),
         *s_pad = fcp.add("pad"), *s_rotate = fcp.add("rotate");

  Option* og_channels =
      s_grayscale->add('c', "channels",
                       "Which channels to use for grayscale computation (use "
                       "'r', 'g', or 'b' for each channel, more letters mean "
                       "average of given channels, e.g. rg is average of red "
                       "and green)");
  Option *oc_x = s_cut->add('x', "",
                            "x possition of the upper left corner of the cut",
                            OT_Int),
         *oc_y = s_cut->add('y', "",
                            "y possition of the upper left corner of the cut",
                            OT_Int),
         *oc_width = s_cut->add('w', "width", "width of the cut", OT_Int),
         *oc_height = s_cut->add('h', "height", "height of the cut", OT_Int);
  Option *op_top = s_pad->add('t', "top", "top padding", OT_Int),
         *op_bottom = s_pad->add('b', "bottom", "bottom padding", OT_Int),
         *op_left = s_pad->add('l', "left", "left padding", OT_Int),
         *op_right = s_pad->add('r', "right", "right padding", OT_Int),
         *op_all = s_pad->add('a', "all", "padding for all sides", OT_Int),
         *op_color = s_pad->add(
             'c', "color", "color of the padding (in format r,g,b or r,g,b,a)");
  Option *or_direction = s_rotate->add('d', "direction",
                                       "rotation direction [left, right]"),
         *or_left = s_rotate->add('l', "left", "rotate left"),
         *or_right = s_rotate->add('r', "right", "rotate right");
  or_left->setNeedsParameter(false);
  or_right->setNeedsParameter(false);

  Parser* found = fcp.parse(argc - 1, argv + 1);
  if (found == nullptr) {
    return 4;
  }
  /*
if (!found->extra().empty()) {
found->dump();
die("Unknown command");
}*/
  // assert(found->extra().empty());
  // found->dump();

  Image img = decodePNG(fcp.inputFile());

  while (found != nullptr) {
    if (found == s_grayscale) {
      if (!og_channels->hasValue()) {
        img = grayscale(img, "rgb");
      } else {
        img = grayscale(img, og_channels->getString());
      }
    } else if (found == s_cut) {
      int x = 0;
      int y = 0;
      int width = img.width();
      int height = img.height();
      if (oc_x->hasValue())
        x = oc_x->getInt();
      if (oc_y->hasValue())
        y = oc_y->getInt();
      if (oc_width->hasValue())
        width = oc_width->getInt();
      if (oc_height->hasValue())
        height = oc_height->getInt();
      if ((x < 0) || (y < 0) || width < 0 || height < 0)
        die("Negative parameters for cut");
      img = cut(img, x, y, width, height);
    } else if (found == s_pad) {
      int left = 0, right = 0, top = 0, bottom = 0;
      if (op_all->hasValue())
        left = right = top = bottom = op_all->getInt();
      if (op_left->hasValue())
        left = op_left->getInt();
      if (op_right->hasValue())
        right = op_right->getInt();
      if (op_top->hasValue())
        top = op_top->getInt();
      if (op_bottom->hasValue())
        bottom = op_bottom->getInt();
      Pixel fill;
      if (op_color->hasValue())
        parseColor(op_color->getString(), fill);
      /*if (!parseColor(op_color->getString(), fill)) {
        std::cerr << "Parse error, expected color, got " <<
op_color->getString() << std::endl;
        return 1;
}*/
      if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
        die("Negative input for padding");
      img = pad(img, top, left, bottom, right, fill);
    } else if (found == s_rotate) {
      Direction d;
      if (or_direction->hasValue() + or_left->hasValue() +
              or_right->hasValue() >
          1) {
        die("Multiple directions entered! Only one expected!");
      }
      if (or_left->hasValue())
        d = Direction::D_Left;
      else if (or_right->hasValue())
        d = Direction::D_Right;
      else if (or_direction->getString() == std::string("left"))
        d = Direction::D_Left;
      else if (or_direction->getString() == std::string("right"))
        d = Direction::D_Right;
      else {
        std::cerr << "Parse error in option --direction, expected 'left' or "
                     "'right', got "
                  << or_direction->getString() << std::endl;
        return 1;
      }
      img = rotate(img, d);
    } else {
      std::cerr << "Unknow command" << std::endl;
      found->dump();
      return 1;
    }

    // auto some = found->extra().at(0);
    if (found->extra().empty())
      found = nullptr;  // if there are no more commands
    else {
      auto found2 = fcp.getSubcommands().find(*(found->extra().begin()));

      if (found2 ==
          fcp.getSubcommands().end()) {  // command not found in database
        std::cerr << "Unknow command" << std::endl;
        return 1;
      }
      for (;; argv++) {
        if (*argv == *found->getExtra().begin())
          break;
      }
      found =
          found2->second.get();  // point to the next requested parser (command)
      argv++;
      found->parse(argv);
    }
  }

  if (img.valid()) {
    if (encodePNG(fcp.outputFile().c_str(), img))
      return 0;
    std::cerr << "Error writting the file" << std::endl;
    return 2;
  }
  std::cerr << "An error occurred, not writting" << std::endl;
  return 3;
}

// check cli classes fcp -> parser -> Option -> OptionVal
// check compatibility
// check image
// check tools

/*
 * each class:
 * check const in attributes
 * check const after functions
 * check const in return type
 * check const in function operands
*/