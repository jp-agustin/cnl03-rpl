#ifndef RPL_METRIC_H
#define RPL_METRIC_H

#include "ns3/header.h"

namespace ns3 {

class RplMetric
{
public:

  /**
   * \brief Constructor.
   */
  RplMetric (void);

  /**
   * \brief Destructor.
   */
  ~RplMetric ();


};

class RplHopCountMetric : public RplMetric
{
  public:

  /**
   * \brief Constructor.
   */
  RplHopCountMetric (void);

  /**
   * \brief Destructor.
   */
  ~RplHopCountMetric ();

  /**
   * \brief Get Hop Count
   * \return hop count
   */
  uint8_t GetHopCount(void) const;

  /**
   * \brief Set Hop Count
   * \param hopCount the hop count
   */
  void SetHopCount(uint8_t hopCount);

private:

  /**
   * \brief The hop count.
   */
  uint8_t m_hopCount;
};

}
#endif
