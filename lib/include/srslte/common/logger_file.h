/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsUE library.
 *
 * srsUE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsUE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

/******************************************************************************
 * File:        logger_file.h
 * Description: Common log object. Maintains a queue of log messages
 *              and runs a thread to read messages and write to file.
 *              Multiple producers, single consumer. If full, producers
 *              increase queue size. If empty, consumer blocks.
 *****************************************************************************/

#ifndef LOGGER_FILE_H
#define LOGGER_FILE_H

#include <stdio.h>
#include <deque>
#include <string>
#include "srslte/common/logger.h"
#include "srslte/common/threads.h"

namespace srslte {

typedef std::string* str_ptr;

class logger_file : public thread, public logger
{
public:
  logger_file();
  logger_file(std::string file);
  ~logger_file();
  void init(std::string file);
  // Implementation of log_out
  void log(str_ptr msg);
  void log(const char *msg);

private:
  void run_thread(); 
  void flush();

  FILE*                 logfile;
  bool                  inited;
  bool                  not_done;
  std::string           filename;
  pthread_cond_t        not_empty;
  pthread_cond_t        not_full;
  pthread_mutex_t       mutex;
  pthread_t             thread;
  std::deque<str_ptr> buffer;
};

} // namespace srsue

#endif // LOGGER_H
