#ifndef CONSOLE_MESSAGE_H
#define CONSOLE_MESSAGE_H

#ifdef DEBUG
    #include <stdio.h>
    #define CONSOLE_INFO(log_format, log_args...) \
        fprintf(stdout, "[%s:%s:%d]: " log_format "\n", __FILE__, __FUNCTION__, __LINE__, ## log_args)
#else
    #define CONSOLE_INFO(log_format, log_args...)
#endif

#endif // CONSOLE_MESSAGE_H