#ifndef __BOOST_ASSERTION_FAILED_MSG_HH__
#define __BOOST_ASSERTION_FAILED_MSG_HH__

#define BOOST_ENABLE_ASSERT_HANDLER

#include <iostream>

namespace boost
{
    void assertion_failed_msg(char const * expr, char const * msg,
        char const * function, char const * file, long line){
      std::cout << "- The assertion < " << expr << " > failed." << std::endl;
      std::cout << "-  file     : < " << file     << " >" << std::endl;
      std::cout << "-  function : < " << function << " >" << std::endl;
      std::cout << "-  line     : < " << line     << " >" << std::endl;
      std::cout << "-  Solution : < " << msg      << " >" << std::endl;
      exit(EXIT_FAILURE);
    }

    void assertion_failed(char const* expr, char const* msg, char const* function , long line){
        assertion_failed_msg(expr, msg, function, "no-file", line);
    }
};

#endif
