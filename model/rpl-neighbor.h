
#ifndef RPL_NEIGHBOR_H
#define RPL_NEIGHBOR_H

#include "ns3/ipv6-address.h"
#include "ns3/simple-ref-count.h"
#include <list>

namespace ns3 {

  /* \ingroup rpl
   * RPL neighbor.
  */

enum neighborType {

  diffDodag = 0x00,
  subDodag = 0x01,
  dodagParent = 0x02,
  daoParent = 0x03,
  prefParent = 0x04

};

class Neighbor : public SimpleRefCount<Neighbor>
{

public:

  /**
   * \brief Get the Neighbor address.
   * \return address
   */
  Ipv6Address GetNeighborAddress(void) const;

  /**
   * \brief Set the Neighbor address.
   * \param address the address of the neighbor
   */
  void SetNeighborAddress(Ipv6Address address);

  /**
   * \brief Get the Neighbor dodagId.
   * \return dodagId
   */
 Ipv6Address GetDodagId(void) const;

  /**
   * \brief Set the Neighbor dodagId.
   * \param dodagId the dodagId of the neighbor
   */
  void SetDodagId(Ipv6Address dodagId);

  /**
   * \brief Get the Neighbor dtsn.
   * \return dtsn
   */
  uint8_t GetDtsn(void) const;
  /**
   * \brief Set the Neighbor dtsn.
   * \param dtsn the dtsn of the neighbor
   */
  void SetDtsn(uint8_t dtsn);

  /**
   * \brief Get the Neighbor rank.
   * \return rank
   */
  uint16_t GetRank(void) const;

  /**
   * \brief Set the Neighbor rank.
   * \param rank the rank of the neighbor
   */
  void SetRank(uint16_t rank);

  /**
   * \brief Get the Neighbor interface.
   * \return interface
   */
  uint32_t GetInterface(void) const;

  /**
   * \brief Set the Neighbor interface.
   * \param interface the interface of the neighbor
   */
  void SetInterface(uint32_t interface);

  /**
   * \brief Get the Neighbor Type.
   * \return type
   */
  uint32_t GetNeighborType(void) const;

  /**
   * \brief Set the Neighbor Type.
   * \param type the neighborType of the neighbor
   */
  void SetNeighborType(neighborType type);

  /**
   * \brief Get reachability.
   * \return reachable
   */
  bool GetReachable(void) const;

  /**
   * \brief Set the Neighbor Reachability.
   * \param reach the reachability of the neighbor
   */
  void SetReachable(bool reach);


private:

  //mainAddress of neigbor with link to main address
  Ipv6Address m_address;
  //dodagId of neighbor
  Ipv6Address m_dodagId;
  //dtsn of neighbor
  uint8_t m_dtsn;
  //rank of neighbor
  uint16_t m_rank;
  //interface of neighbor
  uint32_t m_interface;
  //type of neighbor
  neighborType m_type;
  //reachability
  bool m_reachability;
};

  typedef std::list<Neighbor> NeighborList;

  typedef std::list<Neighbor>::const_iterator NeighborListCI;

}


#endif

/*
struct Neighbor : public SimpleRefCount<Neighbor>
{
  //mainAddress of node who has selected this as neighbor
  //Ipv6Address m_mainAddr;
  //mainAddress of neigbor with link to main address
  Ipv6Address address;
  //dodagId of neighbor
  Ipv6Address dodagId;
  //dtsn of neighbor
  uint8_t dtsn;
  //rank of neighbor
  uint16_t rank;
  //interface of neighbor
  uint32_t interface;
  //reachable neighbor
  bool reachable;
  //NUD number
  //Type of neighbor
   *
   *(1) a node that is not in the same DODAG
   *(2) a node that belongs to the node’s sub-DODAG (therefore with higher rank) 
   *(3) a DODAG parent (therefore with lower rank) 
   *(4) a DAO parent (a DODAG parent selected to send the DAOs to)
   *(5) a preferred DODAG or DAO parent. According tothe neighbor’s kind, a different message processing is triggered.
  /
  neighborType type;   
};
*/

  

