	/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 *
 * Authors: John Patrick Agustin <jcagustin3@up.edu.ph>
 *          Joshua Jacinto <jhjacinto@up.edu.ph>
 */

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

//NS_OBJECT_ENSURE_REGISTERED (Rpl);

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

//Default, ETX is used.
uint16_t RplObjectiveFunctionMhrof::ComputeRank (uint8_t metric)
{
  //Hopcount metric is forced.
  return (uint16_t)metric + 1;
}

/*
uint16_t RplObjectiveFunctionMhrof::ComputeRank (uint16_t parentRank, Metric)
{
  return m_rank;
}
*/

}