#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool helper(
    size_t day, // the current day we are filling up 
    size_t currSlot, // the current slot we are filling up
    vector<size_t>& shiftNum, // stores the number of shifts for a specific worker
    const AvailabilityMatrix& avail, // availability matrix
    const size_t dailyNeed, // daily need 
    const size_t maxShifts,
    DailySchedule& sched 
  );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));

    // Get the number of workers from the availability matrix
    size_t k = avail[0].size();

    // create a vector to count how many shifts are assigned to each worker
    // each index represents a worker and the value represents the number of shifts
    vector<size_t> shiftNum(k, 0);

    bool results = helper(0, 0, shiftNum, avail, dailyNeed, maxShifts, sched);
    return results;
}


bool helper(
    size_t day, // the current day we are filling up 
    size_t currSlot, // the current slot we are filling up
    vector<size_t>& shiftNum, // stores the numbers of shifts per worker
    const AvailabilityMatrix& avail, // availability matrix
    const size_t dailyNeed, // daily need 
    const size_t maxShifts,
    DailySchedule& sched
    )
{

    // Get the number of days from the availability matrix
    size_t n = avail.size();

    // base case: we have filled all the days in the schedule
    if(day == n){
        return true;
    }

    // once we fill the slots for the current day, we can recursively move on to the next day
    if (currSlot >= dailyNeed){
        return helper(day +1, 0, shiftNum, avail, dailyNeed, maxShifts, sched);
    }

    // Get the number of workers from the availability matrix
    size_t k = avail[0].size();

    // if we are here, we still need to fill up the slots of the day
    for(Worker_T worker =0; worker < k; worker++){
      
      // check if the worker is availabile and has yet to reach max shifts
      if(avail[day][worker] && shiftNum[worker] < maxShifts){
        
        // create a boolean for the next loop
        bool booked = false;
        
        // check if the worker is already scheduled
        for (size_t j = 0; j < currSlot; j++){
          if(sched[day][j] == worker){
            booked = true;
            break;
          }
        }

        if(!booked){
          
          // schedule the worker
          sched[day][currSlot] = worker;
          // increase the worker's shift count
          shiftNum[worker]++;

          // recurse to the next slot
          bool results = helper(day, currSlot+1, shiftNum, avail, dailyNeed, maxShifts, sched);
          if(results == true){
            return true;
          }

          // backtrack if a valid schedule could not be built (ie. the return true was not hit)
          sched[day][currSlot] = INVALID_ID;
          shiftNum[worker]--;

        }
      }
    }

    // if we are here, that means all workers have been tried and a valid schedule could not be built
    return false;

}

