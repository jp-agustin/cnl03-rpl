
#define DEFAULT_STEP_OF_RANK 3
#define MINIMUM_STEP_OF_RANK 1
#define MAXIMUM_STEP_OF_RANK 9
#define DEFAULT_RANK_STRETCH 0
#define MAXIMUM_RANK_STRETCH 5
#define DEFAULT_RANK_FACTOR 1
#define MINIMUM_RANK_FACTOR 1
#define MAXIMUM_RANK_FACTOR 4
#define DEFAULT_MIN_HOP_RANK_INCREASE 256

#include <stdint.h>

#include "ns3/log.h"
#include "rpl-objective-function.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplObjectiveFunction");


RplObjectiveFunction::RplObjectiveFunction ()
{ 
}

RplObjectiveFunction::~RplObjectiveFunction ()
{	
}

uint16_t RplObjectiveFunction::ComputeRank (uint16_t parentRank)
{
  return parentRank;
}

RplObjectiveFunctionOf0::RplObjectiveFunctionOf0 ()
{ 
}

RplObjectiveFunctionOf0::~RplObjectiveFunctionOf0 ()
{	
}

uint16_t RplObjectiveFunctionOf0::ComputeRank (uint16_t parentRank)
{
  uint16_t m_rankIncrease = ((DEFAULT_RANK_FACTOR * DEFAULT_STEP_OF_RANK) 
                            + DEFAULT_RANK_STRETCH) * DEFAULT_MIN_HOP_RANK_INCREASE;
  uint16_t m_rank = parentRank + m_rankIncrease;

  return m_rank;
}


RplObjectiveFunctionMhrof::RplObjectiveFunctionMhrof (void)
{
}

RplObjectiveFunctionMhrof::~RplObjectiveFunctionMhrof ()
{
}

uint16_t RplObjectiveFunctionMhrof::ComputeRank (uint8_t metric)
{
  return (uint16_t)metric + 1;
}

}