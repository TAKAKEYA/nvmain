/*
 *  This file is part of NVMain- A cycle accurate timing, bit-accurate
 *  energy simulator for non-volatile memory. Originally developed by 
 *  Matt Poremba at the Pennsylvania State University.
 *
 *  Website: http://www.cse.psu.edu/~poremba/nvmain/
 *  Email: mrp5060@psu.edu
 *
 *  ---------------------------------------------------------------------
 *
 *  If you use this software for publishable research, please include 
 *  the original NVMain paper in the citation list and mention the use 
 *  of NVMain.
 *
 */

#ifndef __MEMORYCONTROLLERMESSAGE_H__
#define __MEMORYCONTROLLERMESSAGE_H__


namespace NVM {


class MemoryControllerMessage
{
 public:
  MemoryControllerMessage( );
  ~MemoryControllerMessage( );


  unsigned int src;
  unsigned int dest;
  int latency;
  void *message;
  
};


};


#endif


