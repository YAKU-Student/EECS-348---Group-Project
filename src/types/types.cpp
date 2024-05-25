// Author: Caden LeCluyse

#include "types.h"

namespace Types {

[[nodiscard]] bool isoperand(const char token) noexcept { return (token == 'T' || token == 'F'); }

[[nodiscard]] bool isoperator(const char token) noexcept {
    return (token == '&' || token == '|' || token == '@' || token == '$');
}

[[nodiscard]] bool isnot(const char token) noexcept { return token == '!'; }

}  // namespace Types
