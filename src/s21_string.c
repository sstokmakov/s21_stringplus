#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *cstr = (void *)str;
  void *result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (*(cstr++) == (unsigned char)c) {
      result = cstr - 1;
      i = n;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  s21_size_t i;
  int result = 0;
  unsigned char *cstr1 = (void *)str1;
  unsigned char *cstr2 = (void *)str2;
  for (i = 0; i < n; i++) {
    result = *(cstr1++) - *(cstr2++);
    if (result != 0) i = n;
  }
  if (result) result = (result < 0) ? -1 : 1;
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  int i, m;
  unsigned long *wdst = dest;
  unsigned long *wsrc = (void *)src;
  unsigned char *cdst, *csrc;
  for (i = 0, m = n / sizeof(long); i < m; i++) *(wdst++) = *(wsrc++);
  cdst = (unsigned char *)wdst;
  csrc = (unsigned char *)wsrc;
  for (i = 0, m = n % sizeof(long); i < m; i++) *(cdst++) = *(csrc++);
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *cstr = str;
  for (s21_size_t i = 0; i < n; i++) *(cstr++) = (unsigned char)c;
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t offset = s21_strlen(dest);
  for (i = 0; *src && i < n; i++) *(dest + offset + i) = *src++;
  *(dest + offset + i) = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str && *str != (char)c) str++;
  return *str || c == '\0' ? (char *)str : s21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i;
  int result = 0;
  for (i = 0; *str1 && *str2 && i < n; i++) {
    result = *(str1++) - *(str2++);
    if (result != 0) break;
  }
  return *str1 && *str2 ? result : *str1 - *str2;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (i = 0; i < n; i++) {
    *(dest + i) = *src ? *(src++) : '\0';
  }
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i;
  for (i = 0; *(src + i); i++) *(dest + i) = *(src + i);
  *(dest + i) = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  while (*str1 && !s21_strchr(str2, *str1++)) result++;
  return result;
}

char *s21_strerror(int errnum) {
#if defined(__APPLE__)
#define MAX_ERRORS 106
#define MIN_ERRORS 0

  static const char *errors[] = {
      "Undefined error: 0",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "Device not configured",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource deadlock avoided",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Resource busy",
      "File exists",
      "Cross-device link",
      "Operation not supported by device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Result too large",
      "Resource temporarily unavailable",
      "Operation now in progress",
      "Operation already in progress",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol family",
      "Address already in use",
      "Can't assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Socket is already connected",
      "Socket is not connected",
      "Can't send after socket shutdown",
      "Too many references: can't splice",
      "Operation timed out",
      "Connection refused",
      "Too many levels of symbolic links",
      "File name too long",
      "Host is down",
      "No route to host",
      "Directory not empty",
      "Too many processes",
      "Too many users",
      "Disc quota exceeded",
      "Stale NFS file handle",
      "Too many levels of remote in path",
      "RPC struct is bad",
      "RPC version wrong",
      "RPC prog. not avail",
      "Program version wrong",
      "Bad procedure for program",
      "No locks available",
      "Function not implemented",
      "Inappropriate file type or format",
      "Authentication error",
      "Need authenticator",
      "Device power is off",
      "Device error",
      "Value too large to be stored in data type",
      "Bad executable (or shared library)",
      "Bad CPU type in executable",
      "Shared library version mismatch",
      "Malformed Mach-o file",
      "Operation canceled",
      "Identifier removed",
      "No message of desired type",
      "Illegal byte sequence",
      "Attribute not found",
      "Bad message",
      "EMULTIHOP (Reserved)",
      "No message available on STREAM",
      "ENOLINK (Reserved)",
      "No STREAM resources",
      "Not a STREAM",
      "Protocol error",
      "STREAM ioctl timeout",
      "Operation not supported on socket",
      "Policy not found",
      "State not recoverable",
      "Previous owner died",
      "Interface output queue is full"};
#elif defined(__linux__)
#define MAX_ERRORS 133
#define MIN_ERRORS 0
  static const char *errorArray[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
#endif
  static char res[128] = {'\0'};
  if (errnum < MIN_ERRORS || errnum > MAX_ERRORS) {
#if defined(__APPLE__)
    { s21_sprintf(res, "Unknown error: %d", errnum); }
#elif defined(__linux__)
    { s21_sprintf(res, "Unknown error %d", errnum); }
#endif
  } else {
#if defined(__APPLE__)
    s21_strncpy(res, ((char *)errors[errnum]), 128);
#elif defined(__linux__)
    s21_strncpy(res, ((char *)errorArray[errnum]), 128);
#endif
  }
  return res;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t size = 0;
  while (*str++) size++;
  return size;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1 && !s21_strchr(str2, *str1)) str1++;
  return *str1 ? (char *)str1 : s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str) {
    if (*(str++) == (char)c) result = (char *)str - 1;
  }
  return c == '\0' ? (char *)str : result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (!(*needle)) return (char *)haystack;
  char *answer = s21_NULL;
  char *ptr_needle = (char *)needle;
  while (*haystack && *ptr_needle) {
    if (*haystack != *ptr_needle) {
      answer = s21_NULL;
      ptr_needle = (char *)needle;
    } else {
      if (!answer) answer = (char *)haystack;
      ptr_needle++;
    }
    haystack++;
  }
  return *ptr_needle ? s21_NULL : answer;
}

char *s21_strtok(char *str, const char *delim) {
  if (!(*delim)) return str;
  static char *start = s21_NULL;
  char *end = s21_NULL;
  char *result = s21_NULL;
  if (str) start = str;
  if (start) end = s21_strpbrk(start, delim);
  if (end) {
    *end = '\0';
    result = start;
    start = end + 1;
  } else if (!str) {
    result = start;
    start = s21_NULL;
  }
  return result && !s21_strlen(result) ? s21_strtok(start, delim) : result;
}

void *s21_to_upper(const char *str) {
  if (!str) return s21_NULL;
  s21_size_t len = s21_strlen(str);
  char *upper_str = (char *)malloc(len + 1);
  for (s21_size_t i = 0; i < len; i++) {
    if (*(str + i) >= 97 && *(str + i) <= 122) {
      *(upper_str + i) = *(str + i) - 32;
    } else {
      *(upper_str + i) = *(str + i);
    }
  }
  *(upper_str + len) = '\0';
  return upper_str;
}

void *s21_to_lower(const char *str) {
  if (!str) return s21_NULL;
  s21_size_t len = s21_strlen(str);
  char *lower_str = (char *)malloc(len + 1);
  for (s21_size_t i = 0; i < len; i++) {
    if (*(str + i) >= 65 && *(str + i) <= 90) {
      *(lower_str + i) = *(str + i) + 32;
    } else {
      *(lower_str + i) = *(str + i);
    }
  }
  *(lower_str + len) = '\0';
  return lower_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  char *result_str = s21_NULL;
  if (start_index <= src_len) {
    result_str = (char *)malloc(src_len + str_len + 1);
    s21_strncpy(result_str, src, start_index);
    s21_strncpy(result_str + start_index, str, str_len);
    s21_strncpy(result_str + start_index + str_len, src + start_index,
                src_len - start_index);
    *(result_str + src_len + str_len) = '\0';
  }
  return result_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) return s21_NULL;
  char *res = s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  const char *end = src + src_len - 1;
  while (*src && s21_strchr(trim_chars, *src)) src++;
  while (end > src && s21_strchr(trim_chars, *end)) end--;
  s21_size_t res_len = end - src + 1;
  res = malloc(res_len + 1);
  res = s21_strncpy(res, src, res_len);
  *(res + res_len) = '\0';
  return (void *)res;
}

s21_size_t s21_itoa_reverse(char **number, long long n) {
  s21_size_t size = 0;
  if (!(size)) {
    size = 1;
    *number = calloc(size + 1, sizeof(char));
  }
  s21_size_t length = 0;
  if (n < 0) n = -n;
  do {
    *(*number + length++) = n % 10 + '0';
    if (length == size) {
      size *= 2;
      *number = realloc(*number, size + 100);
    }
  } while ((n /= 10) > 0);
  *(*number + length) = '\0';
  return length;
}

s21_size_t s21_uitoa_reverse(char **number, unsigned long long n) {
  s21_size_t size = 0;
  if (!(size)) {
    size = 1;
    *number = malloc(size + 1);
  }
  s21_size_t length = 0;
  do {
    *(*number + length++) = n % 10 + '0';
    if (length == size) {
      size *= 2;
      *number = realloc(*number, size + 100);
    }
  } while ((n /= 10) > 0);
  *(*number + length) = '\0';
  return length;
}

s21_size_t s21_itoa(char **number, long long n, int precision,
                    struct flags *flags) {
  s21_size_t length = s21_itoa_reverse(number, n);
  while ((s21_size_t)precision > length) *(*number + length++) = '0';
  if (n < 0) {
    *(*number + length++) = '-';
  } else {
    if (flags->flag_plus) *(*number + length++) = '+';
    if (flags->flag_space) *(*number + length++) = ' ';
  }
  *(*number + length) = '\0';
  s21_reverse(*number);
  return length;
}

s21_size_t s21_uitoa(char **number, unsigned long long n, int precision) {
  s21_size_t length = s21_uitoa_reverse(number, n);
  while ((s21_size_t)precision > length) *(*number + length++) = '0';
  *(*number + length) = '\0';
  s21_reverse(*number);
  return length;
}

s21_size_t s21_ftoa(char **number, double n, int precision,
                    struct flags *flags) {
  long ipart = (long)n;
  char *str_ipart = s21_NULL;
  s21_size_t length = 0;
  double fpart = (n < 0) ? (double)ipart - n : n - (double)ipart;
  if (precision) {
    s21_size_t length_ipart = s21_itoa_reverse(&str_ipart, ipart);
    s21_size_t count_zero = 0;
    for (int i = 1; i <= precision; i++) {
      fpart *= 10;
      if (fpart < 1 && i < precision) count_zero++;
    }
    fpart = round(fpart);
    char *str_fpart = s21_NULL;
    s21_size_t length_fpart =
        s21_uitoa_reverse(&str_fpart, (unsigned long)fpart);
    length = length_fpart + length_ipart + 1 + count_zero;
    *number = calloc(length + 10, sizeof(char));
    *number = s21_strcpy(*number, str_fpart);
    for (s21_size_t i = 0; i < count_zero; i++)
      *(*number + length_fpart + i) = '0';
    *(*number + length_fpart + count_zero) = '.';
    s21_strcpy(*number + length_fpart + 1 + count_zero, str_ipart);
    free(str_fpart);
  } else {
    length = s21_itoa_reverse(&str_ipart, (long long)round(n));
    *number = calloc(length + 10, sizeof(char));
    if (*number) *number = s21_strcpy(*number, str_ipart);
  }
  if (n < 0) {
    *(*number + length++) = '-';
  } else {
    if (flags->flag_plus) *(*number + length++) = '+';
    if (flags->flag_space) *(*number + length++) = ' ';
  }
  s21_reverse(*number);
  free(str_ipart);
  return length;
}

void s21_reverse(char *s) {
  char buff = 0;
  for (s21_size_t i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    buff = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = buff;
  }
}

s21_size_t s21_read_number(const char *c, int *number) {
  char *str_number = calloc(s21_strlen(c) + 1, sizeof(char));
  s21_size_t offset = 0;
  while (*(c + offset) > 47 && *(c + offset) < 58) {
    *(str_number + offset) = *(c + offset);
    offset++;
  }
  *(str_number + offset) = '\0';
  *number = atoi(str_number);
  free(str_number);
  return offset;
}

s21_size_t s21_read_flags(const char *c, struct flags *flags, int *width,
                          int *precision) {
  s21_size_t offset = 0;
  static const char *valid_symbols = " *-+.0123456789hl";

  while (s21_strchr(valid_symbols, *(c + offset))) {
    char buff = *(c + offset);
    if (buff == '-') flags->flag_minus = 1;
    if (buff == '+') flags->flag_plus = 1;
    if (buff == ' ') flags->flag_space = 1;
    if (buff == '.') flags->flag_dot = 1;
    if (buff == 'h') flags->flag_length = 'h';
    if (buff == 'l') flags->flag_length = 'l';
    if (buff > 47 && buff < 58) {
      offset += flags->flag_dot ? s21_read_number(c + offset, precision)
                                : s21_read_number(c + offset, width);
      flags->flag_dot = 0;
    } else {
      offset++;
    }
  }
  if (flags->flag_dot) *precision = 0;
  if (flags->flag_plus) flags->flag_space = 0;
  return offset;
}

void s21_fill_spaces(char *str, int size) {
  int i = 0;
  while (i < size) *(str + i++) = ' ';
  *(str + i) = '\0';
}

void s21_write_string(char **str, char *s, int width, char flag_minus,
                      s21_size_t *length) {
  int buff = width - (int)(*length);
  if (buff < 0) buff = 0;
  if (!flag_minus) {
    s21_fill_spaces(*str, buff);
    *str += buff;
  }
  *str = s21_strncpy(*str, s, *length);
  *(*str + *length) = '\0';
  if (flag_minus) s21_fill_spaces(*str + *length, buff);
  *length += buff;
  *str += s21_strlen(*str);
}

void s21_flag_du_work(char c, unsigned long *un, long *n, struct flags *flags,
                      va_list *args) {
  if ((c == 'u')) {
    flags->flag_plus = 0;
    flags->flag_space = 0;
  }
  if (flags->flag_length == 'l') {
    if (c == 'd') *n = va_arg(*args, long);
    if (c == 'u') *un = va_arg(*args, unsigned long);
  }
  if (flags->flag_length == 'h') {
    if (c == 'd') *n = (short)va_arg(*args, int);
    if (c == 'u') *un = (unsigned short)va_arg(*args, unsigned);
  }
  if (!flags->flag_length) {
    if (c == 'd') *n = va_arg(*args, int);
    if (c == 'u') *un = va_arg(*args, unsigned);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  char *result = str;
  s21_size_t length = 0;
  va_list args;
  va_start(args, format);
  for (const char *c = format; *c; c++) {
    if (*c != '%') {
      *str++ = *c;
      continue;
    }
    char *number = s21_NULL;
    int precision = -1;
    int width = 0;
    struct flags flags = {0};
    c += 1 + s21_read_flags(c + 1, &flags, &width, &precision);
    if (precision == -1 && *c != 's') precision = (*c == 'f') ? 6 : 1;
    if (*c == 'd' || *c == 'u') {
      long n = 0;
      unsigned long un = 0;
      s21_flag_du_work(*c, &un, &n, &flags, &args);
      if (precision || n) {
        length = (*c == 'd') ? s21_itoa(&number, n, precision, &flags)
                             : s21_uitoa(&number, un, precision);
        s21_write_string(&str, number, width, flags.flag_minus, &length);
      }
    } else if (*c == 's') {
      char *s = (char *)va_arg(args, char *);
      length = (precision == -1) ? s21_strlen(s) : (s21_size_t)precision;
      s21_write_string(&str, s, width, flags.flag_minus, &length);
    } else if (*c == 'f') {
      double n = va_arg(args, double);
      length = s21_ftoa(&number, n, precision, &flags);
      s21_write_string(&str, number, width, flags.flag_minus, &length);
    } else {
      char s[2] = " ";
      *s = (*c == 'c') ? (char)va_arg(args, int) : *c;
      length = 1;
      s21_write_string(&str, s, width, flags.flag_minus, &length);
    }
    free(number);
  }
  va_end(args);
  return s21_strlen(result);
}
