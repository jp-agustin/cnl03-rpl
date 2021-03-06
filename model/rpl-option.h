#ifndef RPL_HEADER_OPTION_H
#define RPL_HEADER_OPTION_H

#include <list>
#include "ns3/header.h"
#include "ns3/ipv6-address.h"
#include "ns3/packet.h"
#include "ns3/icmpv6-header.h"

namespace ns3 {

/**
 * \ingroup rpl
 *
 * \brief Route Information Option.
 */

/*
*  \brief (Route Information Option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Type = 0x03  | Option Length | Prefix Length |Resvd|Prf|Resvd|
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                      Route Lifetime                           |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  .                  Prefix (Variable Length)                     .
  .                                                               .
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */


class RplRouteInformationOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplRouteInformationOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplRouteInformationOption ();

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
   * \brief Get the prefix length field.
   * \return the prefix length value
   */
  uint8_t GetPrefixLength () const;

  /**
   * \brief Set the prefix length field.
   * \param prefixLength the prefix length value
   */
  void SetPrefixLength (uint8_t prefixLength);

  /**
   * \brief Get the first reserved.
   * \return the first reserved value
   */
  uint8_t GetReserved1 () const;

  /**
   * \brief Set the first reserved.
   * \param reserved the first reserved value
   */
  void SetReserved1 (uint8_t reserved);

  /**
   * \brief Get the second reserved.
   * \return the second reserved value
   */
  uint8_t GetReserved2 () const;

  /**
   * \brief Set the second reserved.
   * \param reserved the second reserved value
   */
  void SetReserved2 (uint8_t reserved);

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
   * \brief Get the Route Lifetime field.
   * \return the Route Lifetime value
   */
  uint32_t GetRouteLifetime () const;

  /**
   * \brief Set the Route Lifetime fied.
   * \param routeLifetime the Route Lifetime value
   */
  void SetRouteLifetime (uint32_t routeLifetime);

  /**
   * \brief Get the IPv6 prefix.
   * \return IPv6 prefix
   */
  Ipv6Address GetPrefix () const;

  /**
   * \brief Set the IPv6 prefix.
   * \param prefix the IPv6 prefix
   */
  void SetPrefix (Ipv6Address prefix);

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

private:

  /**
   * \brief The first reserved value
   */
  uint8_t m_reserved1;

  /**
   * \brief The second reserved value
   */
  uint8_t m_reserved2;

  /**
   * \brief The PRF field value.
   */
  uint8_t m_prf;

  /**
   * \brief The pathsequence value
   */
  uint8_t m_prefixLength;
  
  /**
   * \brief The route lifetime value
   */
  uint32_t m_routeLifetime;

  /**
   * \brief The prefix value.
   */
  Ipv6Address m_prefix;
};


/**
 * \ingroup rpl
 *
 * \brief Dodag Configuration Option.
 */

/*
*  \brief (Dodag Configuration Option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Type = 0x04  |Opt Length = 14| Flags |A| PCS | DIOIntDoubl.  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  DIOIntMin.   |   DIORedun.   |        MaxRankIncrease        |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |      MinHopRankIncrease       |              OCP              |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |   Reserved    | Def. Lifetime |      Lifetime Unit            |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */


class RplDodagConfigurationOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplDodagConfigurationOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplDodagConfigurationOption ();

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
   * \brief Get the a flag.
   * \return the a flag
   */
  bool GetFlagA () const;

  /**
   * \brief Set the a flag.
   * \param a the flag value
   */
  void SetFlagA (bool a);

  /**
   * \brief Get the Path Control Size field.
   * \return the Path Control Size value
   */
  uint8_t GetPathControlSize () const;

  /**
   * \brief Set the Path Control Size field.
   * \param pcs the Path Control Size value
   */
  void SetPathControlSize (uint8_t pcs);

  /**
   * \brief Get the flags field.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set the flags field.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get the Dio Interval Doublings field.
   * \return the Dio Interval Doublings value
   */
  uint8_t GetDioIntervalDoublings () const;

  /**
   * \brief Set the Dio Interval Doublings field.
   * \param dioIntervalDoublings the Dio Interval Doublings value
   */
  void SetDioIntervalDoublings (uint8_t dioIntervalDoublings);

  /**
   * \brief Get the Dio Interval Min field.
   * \return the Dio Interval Min value
   */
  uint8_t GetDioIntervalMin () const;

  /**
   * \brief Set the Dio Interval Min field.
   * \param dioIntervalMin the Dio Interval Min value
   */
  void SetDioIntervalMin (uint8_t dioIntervalMin);

  /**
   * \brief Get the Dio Redundancy Constant field.
   * \return the Dio Redundancy Constant value
   */
  uint8_t GetDioRedundancyConstant () const;

  /**
   * \brief Set the Dio Redundancy Constant field.
   * \param dioRedundancyConstant the Dio Redundancy Constant value
   */
  void SetDioRedundancyConstant (uint8_t dioRedundancyConstant);

  /**
   * \brief Get the Max Rank Increase field.
   * \return the Max Rank Increase value
   */
  uint16_t GetMaxRankIncrease () const;

  /**
   * \brief Set the Max Rank Increase field.
   * \param maxRankIncrease the Max Rank Increase value
   */
  void SetMaxRankIncrease (uint16_t maxRankIncrease);

  /**
   * \brief Get the Min Hop Rank Increase field.
   * \return the Min Hop Rank Increase value
   */
  uint16_t GetMinHopRankIncrease () const;

  /**
   * \brief Set the Min Hop Rank Increase field.
   * \param minHopRankIncrease the Min Hop Rank Increase value
   */
  void SetMinHopRankIncrease (uint16_t minHopRankIncrease); 

  /**
   * \brief Get the Objective Code Point field.
   * \return the Objective Code Point Increase value
   */
  uint16_t GetObjectiveCodePoint () const;

  /**
   * \brief Set the Objective Code Point field.
   * \param ocp the Objective Code Point value
   */
  void SetObjectiveCodePoint (uint16_t ocp); 

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
   * \brief Get the Default Lifetime field.
   * \return the Default Lifetime value
   */
  uint8_t GetDefaultLifetime () const;

  /**
   * \brief Set the Default Lifetime field.
   * \param defaultLifetime the Default Lifetime value
   */
  void SetDefaultLifetime (uint8_t defaultLifetime);

  /**
   * \brief Get the Lifetime Unit field.
   * \return the Lifetime Unit value
   */
  uint16_t GetLifetimeUnit () const;

  /**
   * \brief Set the Lifetime Unit field.
   * \param lifetimeUnit the Lifetime Unit value
   */
  void SetLifetimeUnit (uint16_t lifetimeUnit);

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

private:

  /**
   * \brief The a flag value
   */
  bool m_flagA;

  /**
   * \brief The path control size value
   */
  uint8_t m_pcs;

  /**
   * \brief The flags value
   */
  uint8_t m_flags;

  /**
   * \brief The Dio Interval Doublings value
   */
  uint8_t m_dioIntervalDoublings;

  /**
   * \brief The Dio Interval Min value
   */
  uint8_t m_dioIntervalMin;

  /**
   * \brief The Dio Redundancy Constant value
   */
  uint8_t m_dioRedundancyConstant;

  /**
   * \brief The Max Rank Increase value
   */
  uint16_t m_maxRankIncrease;

  /**
   * \brief The Min Hop Rank Increase value
   */
  uint16_t m_minHopRankIncrease;

  /**
   * \brief The Objective Code Point value
   */
  uint16_t m_ocp;

  /**
   * \brief The reserved value
   */
  uint8_t m_reserved;

  /**
   * \brief The Default Lifetime value
   */
  uint8_t m_defaultLifetime;

  /**
   * \brief The Lifetime Unit value
   */
  uint16_t m_lifetimeUnit;



};


/**
 * \ingroup rpl
 *
 * \brief Rpl Target Option.
 */

/*
*  \brief (Rpl Target Option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Type = 0x05  | Option Length |      Flags    | Prefix Length |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +                                                               +
  |               Target Prefix (Variable Length)                 |
  .                                                               .
  .                                                               .
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */


class RplTargetOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplTargetOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplTargetOption ();

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
   * \brief Get the flags field.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set the flags field.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get the prefix length field.
   * \return the prefix length value
   */
  uint8_t GetPrefixLength () const;

  /**
   * \brief Set the prefix length field.
   * \param prefixLength the prefix length value
   */
  void SetPrefixLength (uint8_t prefixLength);

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

private:

  /**
   * \brief The flags value
   */
  uint8_t m_flags;

  /**
   * \brief The prefix length value
   */
  uint8_t m_prefixLength;


};

/**
 * \ingroup rpl
 *
 * \brief RPL Transit Information option.
 */

/*
*  \brief (RPL Transit Information option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Type = 0x06  | Option Length |E|    Flags    | Path Control  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | Path Sequence | Path Lifetime |                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               +
  |                                                               |
  +                                                               +
  |                                                               |
  +                        Parent Address*                        +
  |                                                               |
  +                               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */


class RplTransitInformationOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplTransitInformationOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplTransitInformationOption ();

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
   * \brief Get the e flag.
   * \return e flag
   */
  bool GetFlagE () const;

  /**
   * \brief Set the e flag.
   * \param e value
   */
  void SetFlagE (bool e);


  /**
   * \brief Get the flags field.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set the flags field.
   * \param f the flags value
   */
  void SetFlags (uint8_t f);

  /**
   * \brief Get the Path Control field.
   * \return the Path Control value
   */
  uint8_t GetPathControl () const;

  /**
   * \brief Set the pathcontrol field.
   * \param pathcontrol the path control value
   */
  void SetPathControl (uint8_t pathcontrol);

  /**
   * \brief Get the Path Lifetime field.
   * \return the Path Lifetime value
   */
  uint8_t GetPathLifetime () const;

  /**
   * \brief Set the Path Lifetime field.
   * \param pathlifetime the Path Lifetime value
   */
  void SetPathLifetime (uint8_t pathlifetime);  

  /**
   * \brief Get the Path Sequence field.
   * \return the Path Sequence value
   */
  uint8_t GetPathSequence () const;

  /**
   * \brief Set the Path Sequence field.
   * \param pathsequence the Path Sequence value
   */
  void SetPathSequence (uint8_t pathsequence);  

  /**
   * \brief Get Parent Address.
   * \return the Parent Address value
   */
  Ipv6Address GetParentAddress () const;

  /**
   * \brief Set Parent Address.
   * \param parentAddress the Parent Address value
   */
  void SetParentAddress (Ipv6Address parentAddress);

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

private:

  /**
   * \brief The e flag value
   */
  bool m_flagE;

  /**
   * \brief The flags value
   */
  uint8_t m_flags;

  /**
   * \brief The pathsequence value
   */
  uint8_t m_pathSequence;

  /**
   * \brief The pathlifetime value
   */
  uint8_t m_pathLifetime;

  /**
   * \brief The pathcontrol value
   */
  uint8_t m_pathControl;

  /**
   * \brief The Parent Address.
   */
  Ipv6Address m_parentAddress;


};

/**
 * \ingroup rpl
 *
 * \brief RPL Option
 */

/*
*  \brief (RPL Option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
                                  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                  |  Option Type  |  Opt Data Len |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |O|R|F|0|0|0|0|0| RPLInstanceID |          Sender Rank          |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                           (sub-TLVs)                          |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  \endverbatim
 */

class RplOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplOption ();

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
   * \brief Get the e flag.
   * \return e flag
   */
  bool GetFlagO () const;

  /**
   * \brief Set the o flag.
   * \param o value
   */
  void SetFlagO (bool o);

  /**
   * \brief Get the o flag.
   * \return o flag
   */
  bool GetFlagR () const;

  /**
   * \brief Set the r flag.
   * \param r value
   */
  void SetFlagR (bool r);

  /**
   * \brief Get the r flag.
   * \return r flag
   */
  bool GetFlagF () const;

  /**
   * \brief Set the f flag.
   * \param f value
   */
  void SetFlagF (bool f);

  /**
   * \brief Get the flags field.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set the flags field.
   * \param flags the flags value
   */
  void SetFlags (uint8_t flags);

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
   * \brief Get sender rank.
   * \return the sender rank value
   */
  uint16_t GetSenderRank () const;

  /**
   * \brief Set sender rank.
   * \param senderRank the sender rank value
   */
  void SetSenderRank (uint16_t senderRank);  

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

private:
  /**
   * \brief The O flag.
   */
  bool m_flagO;

  /**
   * \brief The R flag.
   */
  bool m_flagR;

  /**
   * \brief The F flag.
   */
  bool m_flagF;

  /**
   * \brief The flags field value.
   */
  uint8_t m_flags;

  /**
   * \brief The RPL Instance ID field value.
   */
  uint8_t m_rplInstanceId;
 
 /**
   * \brief The sender rank value.
   */
  uint16_t m_senderRank;

};

/**
 * \ingroup rpl
 *
 * \brief RPL Solicited Information Option
 */

/*
*  \brief (RPL Solicited Information Option) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Type = 0x07  |Opt Length = 19| RPLInstanceID |V|I|D|  Flags  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                                                               |
  +                                                               +
  |                                                               |
  +                            DODAGID                              +
  |                                                               |
  +                                                               +
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |Version Number |
  +-+-+-+-+-+-+-+-+
  \endverbatim
 */

class RplSolicitedInformationOption: public Icmpv6OptionHeader
{
public:
  /**
   * \brief Constructor.
   */

  RplSolicitedInformationOption ();

  /**
   * \brief Destructor.
   */
  virtual ~RplSolicitedInformationOption ();

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
   * \brief Get the v flag.
   * \return v flag
   */
  bool GetFlagV () const;

  /**
   * \brief Set the v flag.
   * \param v value
   */
  void SetFlagV (bool v);

  /**
   * \brief Get the i flag.
   * \return i flag
   */
  bool GetFlagI () const;

  /**
   * \brief Set the i flag.
   * \param i value
   */
  void SetFlagI (bool i);

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
   * \brief Get the flags field.
   * \return the flags value
   */
  uint8_t GetFlags () const;

  /**
   * \brief Set the flags field.
   * \param flags the flags value
   */
  void SetFlags (uint8_t flags);

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
   * \brief Get DODAG ID.
   * \return the DODAG ID value
   */
  Ipv6Address GetDodagId () const;

  /**
   * \brief Set DODAG ID.
   * \param dodagId the DODAG ID value
   */
  void SetDodagId (Ipv6Address dodagId);

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

private:
  /**
   * \brief The V flag.
   */
  bool m_flagV;

  /**
   * \brief The I flag.
   */
  bool m_flagI;

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
   * \brief The Version number field value.
   */
  uint8_t m_versionNumber;  

  /**
   * \brief The DODAG ID.
   */
  Ipv6Address m_dodagId;

};


}

#endif
