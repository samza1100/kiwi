#ifndef KIWI_STACKFRAME_H
#define KIWI_STACKFRAME_H

#include <memory>
#include <map>
#include <string>
#include <type_traits>
#include <vector>
#include "errors/error.h"
#include "errors/state.h"
#include "parsing/tokens.h"
#include "typing/valuetype.h"

enum class FrameFlags : uint8_t {
  None = 0,
  ReturnFlag = 1 << 0,
  SubFrame = 1 << 1,
  LoopBreak = 1 << 2,
  LoopContinue = 1 << 3,
  InTry = 1 << 4,
  InObject = 1 << 5,
};

inline FrameFlags operator|(FrameFlags a, FrameFlags b) {
  return static_cast<FrameFlags>(
      static_cast<std::underlying_type<FrameFlags>::type>(a) |
      static_cast<std::underlying_type<FrameFlags>::type>(b));
}
inline FrameFlags operator&(FrameFlags a, FrameFlags b) {
  return static_cast<FrameFlags>(
      static_cast<std::underlying_type<FrameFlags>::type>(a) &
      static_cast<std::underlying_type<FrameFlags>::type>(b));
}
inline FrameFlags operator~(FrameFlags a) {
  return static_cast<FrameFlags>(
      ~static_cast<std::underlying_type_t<FrameFlags>>(a));
}

struct CallStackFrame {
  std::vector<Token> tokens;  // The tokens of the current method or scope.
  size_t position = 0;        // Current position in the token stream.
  std::map<std::string, Value> variables;
  Value returnValue;
  ErrorState errorState;
  std::shared_ptr<Object> objectContext;
  FrameFlags flags = FrameFlags::None;

  CallStackFrame(const std::vector<Token>& tokens) : tokens(tokens) {}
  ~CallStackFrame() {
    tokens.clear();
    variables.clear();
  }

  void setErrorState(const KiwiError& e) { errorState.setError(e); }
  bool isErrorStateSet() const { return errorState.isErrorSet(); }
  ErrorState getErrorState() const { return errorState; }
  std::string getErrorMessage() const { return errorState.error.getMessage(); }
  void clearErrorState() { errorState.clearError(); }

  void setObjectContext(const std::shared_ptr<Object>& object) {
    objectContext = object;
    setFlag(FrameFlags::InObject);
  }
  bool inObjectContext() const { return isFlagSet(FrameFlags::InObject); }
  std::shared_ptr<Object>& getObjectContext() { return objectContext; }

  void setFlag(FrameFlags flag) { flags = flags | flag; }
  void clearFlag(FrameFlags flag) { flags = flags & ~flag; }
  bool isFlagSet(FrameFlags flag) const { return (flags & flag) == flag; }
};

#endif