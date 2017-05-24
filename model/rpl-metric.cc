
#include "ns3/rpl-metric.h"

namespace ns3 {

RplMetric::RplMetric ()
{

}

RplMetric::~RplMetric ()
{

}

RplHopCountMetric::RplHopCountMetric (void)
{
  SetHopCount(0);
}

RplHopCountMetric::~RplHopCountMetric ()
{

}

uint8_t RplHopCountMetric::GetHopCount(void) const
{
  return m_hopCount;
}

void RplHopCountMetric::SetHopCount(uint8_t hopCount)
{
  m_hopCount = hopCount;
}

}
