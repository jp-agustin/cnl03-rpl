#ifndef RPL_HEADER_H
#define RPL_HEADER_H

#include <list>
#include "ns3/header.h"
#include "ns3/ipv6-address.h"
#include "ns3/packet.h"
#include "ns3/icmpv6-header.h"

namespace ns3 {

/*
 * \brief (DIS Base Object) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |     Flags     |   Reserved    |           Option(s)...        
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */

class RplDisMessage : public Icmpv6Header
{

public:
  /**
   * \brief Constructor.
   */
  RplDisMessage ();

  /**
   * \brief Destructor.
   */
  virtual ~RplDisMessage ();

  /**
   * \brief Get the UID of this class.
   * \return UID
   */
  static TypeId GetTypeId ();

  /**
   * \brief Get the instance type ID.
   * \return instance type ID
   */
  virtual TypeId GetInstanceTypeId () const;


  /**
   * \brief Print informations.
   * \param os output stream
   */
  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size.
   * \return serialized size
   */
  virtual uint32_t GetSerializedSize () const;

  /**
   * \brief Serialize the packet.
   * \param start start offset
   */
  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start start offset
   * \return length of packet
   */
  virtual uint32_t Deserialize (Buffer::Iterator start);

  /**
   * \brief Get flags.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set flags.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get reserved.
   * \return the reserved value
   */
  uint8_t GetReserved () const;

  /**
   * \brief Set reserved.
   * \param reserved the reserved value
   */
  void SetReserved (uint8_t reserved);

private:
  /**
   * \brief The flags field value.
   */
  uint8_t m_flags;
 
 /**
   * \brief The reserved field value.
   */
  uint8_t m_reserved;

};

/*
*  \brief (DIO Base Object) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | RPLInstanceID |Version Number |              Rank             |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |G|O| MOP | Prf |      DTSN     |    Flags    |     Reserved    |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +                                                               +
  |                                                               |
  +                           DODAGID*                            +
  |                                                               |
  +                                                               +
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | Option(s)...
  +-+-+-+-+-+-+-+
  \endverbatim
 */
class RplDioMessage : public Icmpv6Header
{

public:
  /**
   * \brief Constructor.
   */
  RplDioMessage ();

  /**
   * \brief Destructor.
   */
  virtual ~RplDioMessage ();

  /**
   * \brief Get the UID of this class.
   * \return UID
   */
  static TypeId GetTypeId ();

  /**
   * \brief Get the instance type ID.
   * \return instance type ID
   */
  virtual TypeId GetInstanceTypeId () const;


  /**
   * \brief Print informations.
   * \param os output stream
   */
  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size.
   * \return serialized size
   */
  virtual uint32_t GetSerializedSize () const;

  /**
   * \brief Serialize the packet.
   * \param start start offset
   */
  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start start offset
   * \return length of packet
   */
  virtual uint32_t Deserialize (Buffer::Iterator start);

  /**
   * \brief Get the g flag.
   * \return g flag
   */
  bool GetFlagG () const;

  /**
   * \brief Set the g flag.
   * \param g value
   */
  void SetFlagG (bool g);

  /**
   * \brief Get flags.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set flags.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get rpl instance id.
   * \return the rpl instance id value
   */
  uint8_t GetRplInstanceId () const;

  /**
   * \brief Get MOP.
   * \return the MOP value
   */
  uint8_t GetMop () const;

  /**
   * \brief Set MOP.
   * \param mop the MOP value
   */
  void SetMop (uint8_t mop);

  /**
   * \brief Get Prf.
   * \return the Prf value
   */
  uint8_t GetPrf () const;

  /**
   * \brief Set Prf.
   * \param prf the Prf value
   */
  void SetPrf (uint8_t prf);  

  /**
   * \brief Set rpl instance id.
   * \param r the rpl instance id value
   */
  void SetRplInstanceId (uint8_t rplinstanceid);  

  /**
   * \brief Get reserved.
   * \return the reserved value
   */
  uint8_t GetReserved () const;

  /**
   * \brief Set reserved.
   * \param reserved the reserved value
   */
  void SetReserved (uint8_t reserved);

  /**
   * \brief Get dtsn.
   * \return the dtsn value
   */
  uint8_t GetDtsn () const;

  /**
   * \brief Set dtsn.
   * \param dtsn the dtsn value
   */
  void SetDtsn (uint8_t dtsn);


  /**
   * \brief Get version number.
   * \return the version number value
   */
  uint8_t GetVersionNumber () const;

  /**
   * \brief Set version number.
   * \param version the version number value
   */
  void SetVersionNumber (uint8_t version);

  /**
   * \brief Get rank.
   * \return the rank value
   */
  uint16_t GetRank () const;

  /**
   * \brief Set rank.
   * \param rank the rank value
   */
  void SetRank (uint16_t rank);

  /**
   * \brief Get DODAG ID.
   * \return the DODAG ID value
   */
  Ipv6Address GetDodagId () const;

  /**
   * \brief Set DODAG ID.
   * \param dodagId the DODAG ID value
   */
  void SetDodagId (Ipv6Address dodagId);



private:
  /**
   * \brief The G flag.
   */
  bool m_flagG;

  /**
   * \brief The flags field value.
   */
  uint8_t m_flags;

  /**
   * \brief The MOP field value.
   */
  uint8_t m_mop;

  /**
   * \brief The PRF field value.
   */
  uint8_t m_prf;

  /**
   * \brief The RPL Instance ID field value.
   */
  uint8_t m_rplInstanceId;
 
 /**
   * \brief The reserved field value.
   */
  uint8_t m_reserved;

 /**
   * \brief The rank field value.
   */
  uint16_t m_rank;

 /**
   * \brief The dtsn field value.
   */
  uint8_t m_dtsn;

  /**
   * \brief The version number field value.
   */
  uint8_t m_versionNumber;

  /**
   * \brief The DODAG ID.
   */
  Ipv6Address m_dodagId;
};

/*
*  \brief (DAO Base Object) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | RPLInstanceID |K|D| Flags   |   Reserved      |  DAOSequence  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +                                                               +
  |                           DODAGID*                            |
  +                                                               +
  |                                                               |
  +                                                               +
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | Option(s)...
  +-+-+-+-+-+-+-+
  \endverbatim
 */


class RplDaoMessage : public Icmpv6Header
{

public:
  /**
   * \brief Constructor.
   */
  RplDaoMessage ();

  /**
   * \brief Destructor.
   */
  virtual ~RplDaoMessage ();

  /**
   * \brief Get the UID of this class.
   * \return UID
   */
  static TypeId GetTypeId ();

  /**
   * \brief Get the instance type ID.
   * \return instance type ID
   */
  virtual TypeId GetInstanceTypeId () const;


  /**
   * \brief Print informations.
   * \param os output stream
   */
  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size.
   * \return serialized size
   */
  virtual uint32_t GetSerializedSize () const;

  /**
   * \brief Serialize the packet.
   * \param start start offset
   */
  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start start offset
   * \return length of packet
   */
  virtual uint32_t Deserialize (Buffer::Iterator start);

  /**
   * \brief Get the k flag.
   * \return k flag
   */
  bool GetFlagK () const;

  /**
   * \brief Set the K flag.
   * \param k value
   */
  void SetFlagK (bool k);

  /**
   * \brief Get the d flag.
   * \return d flag
   */
  bool GetFlagD () const;

  /**
   * \brief Set the d flag.
   * \param d value
   */
  void SetFlagD (bool d);

  /**
   * \brief Get flags.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set flags.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get rpl instance id.
   * \return the rpl instance id value
   */
  uint8_t GetRplInstanceId () const;

  /**
   * \brief Set rpl instance id.
   * \param r the rpl instance id value
   */
  void SetRplInstanceId (uint8_t rplinstanceid);  

  /**
   * \brief Get reserved.
   * \return the reserved value
   */
  uint8_t GetReserved () const;

  /**
   * \brief Set reserved.
   * \param reserved the reserved value
   */
  void SetReserved (uint8_t reserved);

  /**
   * \brief Get DAO Sequence.
   * \return the DAO sequnce value
   */
  uint8_t GetDaoSequence () const;

  /**
   * \brief Set DAO sequence.
   * \param sequence the DAO sequence value
   */
  void SetDaoSequence (uint8_t sequence);

  /**
   * \brief Get DODAG ID.
   * \return the DODAG ID value
   */
  Ipv6Address GetDodagId () const;

  /**
   * \brief Set DODAG ID.
   * \param dodagId the DODAG ID value
   */
  void SetDodagId (Ipv6Address dodagId);



private:
  /**
   * \brief The K flag.
   */
  bool m_flagK;

  /**
   * \brief The D flag.
   */
  bool m_flagD;

  /**
   * \brief The flags field value.
   */
  uint8_t m_flags;

  /**
   * \brief The RPL Instance ID field value.
   */
  uint8_t m_rplInstanceId;
 
 /**
   * \brief The reserved field value.
   */
  uint8_t m_reserved;

  /**
   * \brief The dao sequence field value.
   */
  uint8_t m_daoSequence;

  /**
   * \brief The DODAG ID.
   */
  Ipv6Address m_dodagId;
};

/*
*  \brief (DAO-ACK Base Object) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | RPLInstanceID |D| Reserved  |    DAOSequence  |    Status     |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +                                                               +
  |                           DODAGID*                            |
  +                                                               +
  |                                                               |
  +                                                               +
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | Option(s)...
  +-+-+-+-+-+-+-+
  \endverbatim
 */

class RplDaoAckMessage : public Icmpv6Header
{

public:
  /**
   * \brief Constructor.
   */
  RplDaoAckMessage ();

  /**
   * \brief Destructor.
   */
  virtual ~RplDaoAckMessage ();

  /**
   * \brief Get the UID of this class.
   * \return UID
   */
  static TypeId GetTypeId ();

  /**
   * \brief Get the instance type ID.
   * \return instance type ID
   */
  virtual TypeId GetInstanceTypeId () const;


  /**
   * \brief Print informations.
   * \param os output stream
   */
  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size.
   * \return serialized size
   */
  virtual uint32_t GetSerializedSize () const;

  /**
   * \brief Serialize the packet.
   * \param start start offset
   */
  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start start offset
   * \return length of packet
   */
  virtual uint32_t Deserialize (Buffer::Iterator start);


  /**
   * \brief Get the d flag.
   * \return d flag
   */
  bool GetFlagD () const;

  /**
   * \brief Set the d flag.
   * \param d value
   */
  void SetFlagD (bool d);

  /**
   * \brief Get status.
   * \return the status value
   */
  uint8_t GetStatus () const;

  /**
   * \brief Set status.
   * \param f the flags status
   */
  void SetStatus (uint8_t status);

  /**
   * \brief Get rpl instance id.
   * \return the rpl instance id value
   */
  uint8_t GetRplInstanceId () const;

  /**
   * \brief Set rpl instance id.
   * \param r the rpl instance id value
   */
  void SetRplInstanceId (uint8_t rplinstanceid);  

  /**
   * \brief Get reserved.
   * \return the reserved value
   */
  uint8_t GetReserved () const;

  /**
   * \brief Set reserved.
   * \param reserved the reserved value
   */
  void SetReserved (uint8_t reserved);

  /**
   * \brief Get DAO Sequence.
   * \return the DAO sequnce value
   */
  uint8_t GetDaoSequence () const;

  /**
   * \brief Set DAO sequence.
   * \param sequence the DAO sequence value
   */
  void SetDaoSequence (uint8_t sequence);

  /**
   * \brief Get DODAG ID.
   * \return the DODAG ID value
   */
  Ipv6Address GetDodagId () const;

  /**
   * \brief Set DODAG ID.
   * \param dodagId the DODAG ID value
   */
  void SetDodagId (Ipv6Address dodagId);



private:

  /**
   * \brief The D flag.
   */
  bool m_flagD;

  /**
   * \brief The flags field value.
   */
  uint8_t m_status;

  /**
   * \brief The RPL Instance ID field value.
   */
  uint8_t m_rplInstanceId;
 
 /**
   * \brief The reserved field value.
   */
  uint8_t m_reserved;

  /**
   * \brief The dao sequence field value.
   */
  uint8_t m_daoSequence;

  /**
   * \brief The DODAG ID.
   */
  Ipv6Address m_dodagId;
};


}

#endif