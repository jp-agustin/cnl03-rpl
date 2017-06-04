#ifndef RPL_NEIGHBOR_SET_H
#define RPL_NEIGHBOR_SET_H

#include <list>

#include "ns3/ipv6-routing-protocol.h"
#include "ns3/ipv6-interface.h"
#include "rpl-neighbor.h"

namespace ns3 {

class RplNeighborSet
{
public:

  /**
   * \brief Constructor
   */
  RplNeighborSet();

  /**
   * \brief Deconstructor
   */
  ~RplNeighborSet();

  /**
   * \brief Add neighbor to neighborlist.
   * \param neighbor neighbor struct.
   */
  void AddNeighbor(Neighbor neighbor);

  /**
   * \brief delete neighbor from neighborlist.
   * \param address neighbor address
   */
  void DeleteNeighbor(Ipv6Address address);

  /**
   * \brief delete all neighbors from neighborlist.
   */
  void ClearNeighborSet();

  /**
   * \brief find neighbor in neighborlist.
   * \param address neighbor address
   */
  Ptr<Neighbor> FindNeighbor (Ipv6Address address);

  /**
   * \brief Update neighbor in neighborlist.
   * \param address neighbor address
   * \param dodagId neighbor dodagId
   * \param dtsn neighbor dtsn
   * \param rank neighbor rank
   * \param interface neighbor interface
   */
  void UpdateNeighbor(Ipv6Address address, Ipv6Address dodagId, uint8_t dtsn, uint16_t rank, uint32_t interface);

  /**
   * \brief select parent node in neighborlist.
   * \param rank current rank
   */
  Ptr<Neighbor> SelectParent(uint16_t rank);

  /**
   * \brief get parent node in neighborlist.
   */
  Ptr<Neighbor> GetParent();

  /**
   * \brief Get parent Address
   */
  Ipv6Address GetParentAddress();

  /**
   * \brief Clear preferred parent
   */
  void ClearParent ();

  /**
   * \brief Get parent list
   * \param rank parent rank
   */
  NeighborList GetParentList (uint16_t rank);

  /**
   * \brief Clear parent list
   */
  void ClearParentList ();

private:
  
  /*
   * \brief Container for neighbors
   */
  NeighborList m_neighborList;

  /*
   * \brief Preferred Parent
   */
  Ptr<Neighbor> m_prefParent;

  /*
   * \brief Container for parents
   */
  NeighborList m_parentList;
};


}

#endif
