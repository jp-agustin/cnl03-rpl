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
   * \brief Get the UID of this class.
   * \return UID
   */
//  static TypeId GetTypeId ();

  /**
   * \brief Get the instance type ID.
   * \return instance type ID
   */
//  virtual TypeId GetInstanceTypeId () const;

  /**
   * \brief Add neighbor to neighborlist.
   * \param address neighbor address
   * \param dodagId neighbor dodagId
   * \param dtsn neighbor dtsn
   * \param rank neighbor rank
   * \param interface neighbor interface
   */
//  void AddNeighbor(Ipv6Address address, Ipv6Address dodagId, uint8_t dtsn, uint16_t rank, uint32_t interface);

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
   */
  Ptr<Neighbor> SelectParent(uint16_t rank);

  /**
   * \brief get parent node in neighborlist.
   */
  Ipv6Address GetParent();

private:
  // Container for neighbors
  NeighborList m_neighborList;
  // Preferred Parent
  Ptr<Neighbor> m_prefParent;
};


}

#endif
