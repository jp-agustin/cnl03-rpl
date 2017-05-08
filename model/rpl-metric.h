#ifndef RPL_METRIC_H
#define RPL_METRIC_H

#include "ns3/header.h"

namespace ns3 {

  /* \ingroup rpl
   * RPL neighbor.
  */

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

  /**
   * \brief Print informations.
   * \param os output stream
   */
//  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size.
   * \return serialized size
   */
//  virtual uint32_t GetSerializedSize () const;

  /**
   * \brief Serialize the packet.
   * \param start start offset
   */
//  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start start offset
   * \return length of packet
   */
//  virtual uint32_t Deserialize (Buffer::Iterator start);

private:

  /**
   * \brief The hop count.
   */
  uint8_t m_hopCount;
};

}
#endif
