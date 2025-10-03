// below call
std::make_error_code(std::errc::permission_denied)

  // is equivalent to:
std::error_code(static_cast<int>(std::errc::permission_denied), std::generic_category());
