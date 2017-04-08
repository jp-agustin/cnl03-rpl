
#include "ns3/header.h"
#include "ns3/ipv6-address.h"   
#include "ns3/log.h"
#include "ns3/rpl-option.h"
#include "rpl-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplHeaderOptions");

NS_OBJECT_ENSURE_REGISTERED (RplRouteInformationOption);

RplRouteInformationOption::RplRouteInformationOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (3);
  SetPrefix (Ipv6Address ("::"));
  SetPrefixLength (0);
  SetReserved1 (0);
  SetPrf (0);
  SetReserved2 (0);
  SetRouteLifetime (0);
}

RplRouteInformationOption::~RplRouteInformationOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplRouteInformationOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplRouteInformationOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplRouteInformationOption> ()
  ;
  return tid;
}

TypeId RplRouteInformationOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

uint8_t RplRouteInformationOption::GetPrefixLength () const
{
  NS_LOG_FUNCTION (this);
  return m_prefixLength;
}

void RplRouteInformationOption::SetPrefixLength (uint8_t prefixLength)
{
  NS_LOG_FUNCTION (this << prefixLength);
  m_prefixLength = prefixLength;
}

uint8_t RplRouteInformationOption::GetReserved1 () const
{
  NS_LOG_FUNCTION (this);
  return m_reserved1;
}
  
void RplRouteInformationOption::SetReserved1 (uint8_t reserved)
{
  NS_LOG_FUNCTION (this << reserved);
  m_reserved1 = reserved;
}

uint8_t RplRouteInformationOption::GetReserved2 () const
{
  NS_LOG_FUNCTION (this);
  return m_reserved2;
}

void RplRouteInformationOption::SetReserved2 (uint8_t reserved)
{
  NS_LOG_FUNCTION (this << reserved);
  m_reserved2 = reserved;
}

uint8_t RplRouteInformationOption::GetPrf () const
{
  NS_LOG_FUNCTION (this);
  return m_prf;
}

void RplRouteInformationOption::SetPrf (uint8_t prf)
{
  NS_LOG_FUNCTION (this << prf);
  m_prf = prf;
}

uint32_t RplRouteInformationOption::GetRouteLifetime () const
{
  NS_LOG_FUNCTION (this);
  return m_routeLifetime;
}

void RplRouteInformationOption::SetRouteLifetime (uint32_t routeLifetime)
{
  NS_LOG_FUNCTION (this << routeLifetime);
  m_routeLifetime = routeLifetime;
}

Ipv6Address RplRouteInformationOption::GetPrefix () const
{
  NS_LOG_FUNCTION (this);
  return m_prefix;
}

void RplRouteInformationOption::SetPrefix (Ipv6Address prefix)
{
  NS_LOG_FUNCTION (this << prefix);
  m_prefix = prefix;
}

void RplRouteInformationOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " length = " << (uint32_t)GetLength () << " prefix " << m_prefix << ")";
}

uint32_t RplRouteInformationOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 26;
}

void RplRouteInformationOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  uint8_t buf[16];

  memset (buf, 0x00, sizeof (buf));

  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());
  i.WriteU8 (m_prefixLength);
  i.WriteU8 (m_reserved1);
  i.WriteU8 (m_prf);
  i.WriteU8 (m_reserved2);
  i.WriteHtonU32 (m_routeLifetime);
  m_prefix.GetBytes (buf);
  i.Write (buf, 16);
}

uint32_t RplRouteInformationOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  uint8_t buf[16];

  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  SetPrefixLength (i.ReadU8 ());
  SetReserved1 (i.ReadU8 ());
  SetPrf (i.ReadU8 ());
  SetReserved2 (i.ReadU8 ());
  SetRouteLifetime (i.ReadNtohU32 ());
  i.Read (buf, 16);

  Ipv6Address prefix (buf);
  SetPrefix (prefix);

  return GetSerializedSize ();
}


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

NS_OBJECT_ENSURE_REGISTERED (RplDodagConfigurationOption);

RplDodagConfigurationOption::RplDodagConfigurationOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (4);
  SetLength (14);
  SetFlags (0);
  SetDioIntervalDoublings (0);
  SetDioIntervalMin (0);
  SetDioRedundancyConstant (0);
  SetMaxRankIncrease (0);
  SetMinHopRankIncrease (0);
  SetObjectiveCodePoint (0);
  SetReserved (0);
  SetDefaultLifetime (0);
  SetLifetimeUnit (0);
}

RplDodagConfigurationOption::~RplDodagConfigurationOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplDodagConfigurationOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplDodagConfigurationOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplDodagConfigurationOption> ()
  ;
  return tid;
}

TypeId RplDodagConfigurationOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

bool RplDodagConfigurationOption::GetFlagA () const
{
  NS_LOG_FUNCTION (this);
  return m_flagA;
}

void RplDodagConfigurationOption::SetFlagA (bool a)
{
  NS_LOG_FUNCTION (this << a);
  m_flagA = a;
}

uint8_t RplDodagConfigurationOption::GetPathControlSize () const
{
  NS_LOG_FUNCTION (this);
  return m_pcs;
}

void RplDodagConfigurationOption::SetPathControlSize (uint8_t pcs)
{
  NS_LOG_FUNCTION (this << pcs);
  m_pcs = pcs;
}

uint8_t RplDodagConfigurationOption::GetFlags () const
{
  NS_LOG_FUNCTION (this);
  return m_flags;
}

void RplDodagConfigurationOption::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION (this << f);
  m_flags = f;
}

uint8_t RplDodagConfigurationOption::GetDioIntervalDoublings () const
{
  NS_LOG_FUNCTION (this);
  return m_dioIntervalDoublings;
}

void RplDodagConfigurationOption::SetDioIntervalDoublings (uint8_t dioIntervalDoublings)
{
  NS_LOG_FUNCTION (this << dioIntervalDoublings);
  m_dioIntervalDoublings = dioIntervalDoublings;
}

uint8_t RplDodagConfigurationOption::GetDioIntervalMin () const
{
  NS_LOG_FUNCTION (this);
  return m_dioIntervalMin;
}

void RplDodagConfigurationOption::SetDioIntervalMin (uint8_t dioIntervalMin)
{
  NS_LOG_FUNCTION (this << dioIntervalMin);
  m_dioIntervalMin = dioIntervalMin;
}

uint8_t RplDodagConfigurationOption::GetDioRedundancyConstant () const
{
  NS_LOG_FUNCTION (this);
  return m_dioRedundancyConstant;
}

void RplDodagConfigurationOption::SetDioRedundancyConstant (uint8_t dioRedundancyConstant)
{
  NS_LOG_FUNCTION (this << dioRedundancyConstant);
  m_dioRedundancyConstant = dioRedundancyConstant;
}
uint16_t RplDodagConfigurationOption::GetMaxRankIncrease () const
{
  NS_LOG_FUNCTION (this);
  return m_maxRankIncrease;
}

void RplDodagConfigurationOption::SetMaxRankIncrease (uint16_t maxRankIncrease)
{
  NS_LOG_FUNCTION (this << maxRankIncrease);
  m_maxRankIncrease = maxRankIncrease;
}

uint16_t RplDodagConfigurationOption::GetMinHopRankIncrease () const
{
  NS_LOG_FUNCTION (this);
  return m_minHopRankIncrease;
}

void RplDodagConfigurationOption::SetMinHopRankIncrease (uint16_t minHopRankIncrease)
{
  NS_LOG_FUNCTION (this << minHopRankIncrease);
  m_minHopRankIncrease = minHopRankIncrease;
}

uint16_t RplDodagConfigurationOption::GetObjectiveCodePoint () const
{
  NS_LOG_FUNCTION (this);
  return m_ocp;
}

void RplDodagConfigurationOption::SetObjectiveCodePoint (uint16_t ocp) 
{
  NS_LOG_FUNCTION (this << ocp);
  m_ocp = ocp;
}

uint8_t RplDodagConfigurationOption::GetReserved () const
{
  NS_LOG_FUNCTION (this);
  return m_reserved;
}

void RplDodagConfigurationOption::SetReserved (uint8_t reserved)
{
  NS_LOG_FUNCTION (this << reserved);
  m_reserved = reserved;
}

uint8_t RplDodagConfigurationOption::GetDefaultLifetime () const
{
  NS_LOG_FUNCTION (this);
  return m_defaultLifetime;
}

void RplDodagConfigurationOption::SetDefaultLifetime (uint8_t defaultLifetime)
{
  NS_LOG_FUNCTION (this << defaultLifetime);
  m_defaultLifetime = defaultLifetime;
}

uint16_t RplDodagConfigurationOption::GetLifetimeUnit () const
{
  NS_LOG_FUNCTION (this);
  return m_lifetimeUnit;
}

void RplDodagConfigurationOption::SetLifetimeUnit (uint16_t lifetimeUnit)
{
  NS_LOG_FUNCTION (this << lifetimeUnit);
  m_lifetimeUnit = lifetimeUnit;
}

void RplDodagConfigurationOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " length = " << (uint32_t)GetLength () <<")";
}

uint32_t RplDodagConfigurationOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 16;
}

void RplDodagConfigurationOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());
  i.WriteU8 (m_flags); 
  i.WriteU8 (m_dioIntervalDoublings);
  i.WriteU8 (m_dioIntervalMin);
  i.WriteU8 (m_dioRedundancyConstant);
  i.WriteU16 (m_maxRankIncrease);
  i.WriteU16 (m_minHopRankIncrease);
  i.WriteU16 (m_ocp);
  i.WriteU8 (m_reserved);
  i.WriteU8 (m_defaultLifetime);
  i.WriteU16 (m_lifetimeUnit);

}

uint32_t RplDodagConfigurationOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  SetFlags (i.ReadU8 ());
  SetDioIntervalDoublings (i.ReadU8 ());
  SetDioIntervalMin (i.ReadU8 ());
  SetDioRedundancyConstant (i.ReadU8 ());
  SetMaxRankIncrease (i.ReadU16 ());
  SetMinHopRankIncrease (i.ReadU16 ());
  SetObjectiveCodePoint (i.ReadU16 ());
  SetReserved (i.ReadU8 ());
  SetDefaultLifetime (i.ReadU8 ());
  SetLifetimeUnit (i.ReadU16 ());

  return GetSerializedSize ();
}


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

NS_OBJECT_ENSURE_REGISTERED (RplTargetOption);

RplTargetOption::RplTargetOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (5);
  SetFlags (0);
  SetPrefixLength (0);
}


RplTargetOption::~RplTargetOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplTargetOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplTargetOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplTargetOption> ()
  ;
  return tid;
}

TypeId RplTargetOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

uint8_t RplTargetOption::GetFlags () const
{
  NS_LOG_FUNCTION (this);
  return m_flags;
}

void RplTargetOption::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION (this << f);
  m_flags = f;
}

uint8_t RplTargetOption::GetPrefixLength () const
{
  NS_LOG_FUNCTION (this);
  return m_prefixLength;
}

void RplTargetOption::SetPrefixLength (uint8_t prefixLength)
{
  NS_LOG_FUNCTION (this << prefixLength);
  m_prefixLength = prefixLength;
}

void RplTargetOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " length = " << (uint32_t)GetLength () << ")";
}

uint32_t RplTargetOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 20;
}

void RplTargetOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());
  i.WriteU8 (m_prefixLength);
  i.WriteU8 (m_flags);

}

uint32_t RplTargetOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  SetPrefixLength (i.ReadU8 ());
  SetFlags (i.ReadU8 ());

  return GetSerializedSize ();
}


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


NS_OBJECT_ENSURE_REGISTERED (RplTransitInformationOption);

RplTransitInformationOption::RplTransitInformationOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (6);
  SetFlags (0);
  SetPathControl (0);
  SetPathSequence (0);
  SetPathLifetime (0);
  SetParentAddress (Ipv6Address ("::"));
}

RplTransitInformationOption::~RplTransitInformationOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplTransitInformationOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplTransitInformationOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplTransitInformationOption> ()
  ;
  return tid;
}

TypeId RplTransitInformationOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

bool RplTransitInformationOption::GetFlagE () const
{
  NS_LOG_FUNCTION (this);
  return m_flagE;
}

void RplTransitInformationOption::SetFlagE (bool e)
{
  NS_LOG_FUNCTION (this << e);
  m_flagE = e;
}

uint8_t RplTransitInformationOption::GetFlags () const
{
  NS_LOG_FUNCTION (this);
  return m_flags;
}

void RplTransitInformationOption::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION (this << f);
  m_flags = f;
}

uint8_t RplTransitInformationOption::GetPathControl () const
{
  NS_LOG_FUNCTION (this);
  return m_pathControl;
}

void RplTransitInformationOption::SetPathControl (uint8_t pathcontrol)
{
  NS_LOG_FUNCTION (this << pathcontrol);
  m_pathControl = pathcontrol;
}

uint8_t RplTransitInformationOption::GetPathLifetime () const
{
  NS_LOG_FUNCTION (this);
  return m_pathLifetime;
}

void RplTransitInformationOption::SetPathLifetime (uint8_t pathlifetime)
{
  NS_LOG_FUNCTION (this << pathlifetime);
  m_pathLifetime = pathlifetime;
}

uint8_t RplTransitInformationOption::GetPathSequence () const
{
  NS_LOG_FUNCTION (this);
  return m_pathSequence;
}

void RplTransitInformationOption::SetPathSequence (uint8_t pathsequence)
{
  NS_LOG_FUNCTION (this << pathsequence);
  m_pathSequence = pathsequence;
}

Ipv6Address RplTransitInformationOption::GetParentAddress () const
{
  NS_LOG_FUNCTION (this);
  return m_parentAddress;
}

void RplTransitInformationOption::SetParentAddress (Ipv6Address parentAddress)
{
  NS_LOG_FUNCTION (this << parentAddress);
  m_parentAddress = parentAddress;
}

void RplTransitInformationOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () <<")";
}

uint32_t RplTransitInformationOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 22;
}


void RplTransitInformationOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  uint8_t buf[16];

  memset (buf, 0x00, sizeof (buf));

  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());
  i.WriteU8 (m_flags);
  i.WriteU8 (m_pathControl);
  i.WriteU8 (m_pathSequence);
  i.WriteU8 (m_pathLifetime);
  m_parentAddress.GetBytes (buf);
  i.Write (buf, 16);

}

uint32_t RplTransitInformationOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  uint8_t buf[16];

  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  SetFlags (i.ReadU8 ());
  SetPathControl (i.ReadU8 ());
  SetPathSequence (i.ReadU8 ());
  SetPathLifetime (i.ReadU8 ());  
  i.Read (buf, 16);

  Ipv6Address parentAddress (buf);
  SetParentAddress (parentAddress);
  return GetSerializedSize ();
}


NS_OBJECT_ENSURE_REGISTERED (RplOption);

RplOption::RplOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (0);
  SetFlags (0);
  SetRplInstanceId (0);
  SetSenderRank (0);
}

RplOption::~RplOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplOption> ()
  ;
  return tid;
}
TypeId RplOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

bool RplOption::GetFlagO () const
{
  NS_LOG_FUNCTION (this);
  return m_flagO;
}

void RplOption::SetFlagO (bool o)
{
  NS_LOG_FUNCTION (this << o);
  m_flagO = o;
}

bool RplOption::GetFlagR () const
{
  NS_LOG_FUNCTION (this);
  return m_flagR;
}

void RplOption::SetFlagR (bool r)
{
  NS_LOG_FUNCTION (this << r);
  m_flagR = r;
}

bool RplOption::GetFlagF () const
{
  NS_LOG_FUNCTION (this);
  return m_flagF;
}

void RplOption::SetFlagF (bool f)
{
  NS_LOG_FUNCTION (this << f);
  m_flagF = f;
}

uint8_t RplOption::GetFlags () const
{
  NS_LOG_FUNCTION (this);
  return m_flags;
}

void RplOption::SetFlags (uint8_t flags)
{
  NS_LOG_FUNCTION (this << flags);
  m_flags = flags;
}

uint8_t RplOption::GetRplInstanceId () const
{
  NS_LOG_FUNCTION (this);
  return m_rplInstanceId;
}

void RplOption::SetRplInstanceId (uint8_t rplinstanceid)
{
  NS_LOG_FUNCTION (this << rplinstanceid);
  m_rplInstanceId = rplinstanceid;
}

uint16_t RplOption::GetSenderRank () const
{
  NS_LOG_FUNCTION (this);
  return m_senderRank;
}

void RplOption::SetSenderRank (uint16_t senderRank) 
{
  NS_LOG_FUNCTION (this << senderRank);
  m_senderRank = senderRank;
}

void RplOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " length = " << (uint32_t)GetLength () << ")";
}

uint32_t RplOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 6;
}


void RplOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());
  i.WriteU8 (m_flags);
  i.WriteU8 (m_rplInstanceId);
  i.WriteU16 (m_senderRank);
}

uint32_t RplOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  SetFlags (i.ReadU8 ());
  SetRplInstanceId (i.ReadU8 ());
  SetSenderRank (i.ReadU16 ());

  return GetSerializedSize ();
}

NS_OBJECT_ENSURE_REGISTERED (RplSolicitedInformationOption);

RplSolicitedInformationOption::RplSolicitedInformationOption ()
{
  NS_LOG_FUNCTION (this);
  SetType (7);
  SetLength (19);
  SetFlags (0);
  SetRplInstanceId (0);
  SetVersionNumber (0);
}

RplSolicitedInformationOption::~RplSolicitedInformationOption ()
{
  NS_LOG_FUNCTION (this);
}

TypeId RplSolicitedInformationOption::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplSolicitedInformationOption")
    .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplSolicitedInformationOption> ()
  ;
  return tid;
}

TypeId RplSolicitedInformationOption::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

bool RplSolicitedInformationOption::GetFlagV () const
{
  NS_LOG_FUNCTION (this);
  return m_flagV;
}

void RplSolicitedInformationOption::SetFlagV (bool v)
{
  NS_LOG_FUNCTION (this << v);
  m_flagV = v;
}

bool RplSolicitedInformationOption::GetFlagI () const
{
  NS_LOG_FUNCTION (this);
  return m_flagI;
}

void RplSolicitedInformationOption::SetFlagI (bool i)
{
  NS_LOG_FUNCTION (this << i);
  m_flagI = i;
}

bool RplSolicitedInformationOption::GetFlagD () const
{
  NS_LOG_FUNCTION (this);
  return m_flagD;
}

void RplSolicitedInformationOption::SetFlagD (bool d)
{
  NS_LOG_FUNCTION (this << d);
  m_flagD = d;
}

uint8_t RplSolicitedInformationOption::GetFlags () const
{
  NS_LOG_FUNCTION (this);
  return m_flags;
}

void RplSolicitedInformationOption::SetFlags (uint8_t flags)
{
  NS_LOG_FUNCTION (this << flags);
  m_flags = flags;
}

uint8_t RplSolicitedInformationOption::GetRplInstanceId () const
{
  NS_LOG_FUNCTION(this);
  return m_rplInstanceId;
}

void RplSolicitedInformationOption::SetRplInstanceId (uint8_t rplinstanceid)
{
  NS_LOG_FUNCTION(this << rplinstanceid);
  m_rplInstanceId = rplinstanceid;
}

uint8_t RplSolicitedInformationOption::GetVersionNumber () const
{
  NS_LOG_FUNCTION(this);
  return m_versionNumber;
}

void RplSolicitedInformationOption::SetVersionNumber (uint8_t version)
{
  NS_LOG_FUNCTION(this << version);
  m_versionNumber = version;
}

Ipv6Address RplSolicitedInformationOption::GetDodagId () const
{
  NS_LOG_FUNCTION(this);
  return m_dodagId;
}

void RplSolicitedInformationOption::SetDodagId (Ipv6Address dodagId)
{
  NS_LOG_FUNCTION(this << dodagId);
  m_dodagId = dodagId;
}

void RplSolicitedInformationOption::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " length = " << (uint32_t)GetLength () << ")";
}

uint32_t RplSolicitedInformationOption::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 21;
}

void RplSolicitedInformationOption::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buff_dodagId[16];
  Buffer::Iterator i = start;
  uint8_t flags = 0;

  i.WriteU8 (GetType ());
  i.WriteU8 (GetLength ());

  if (m_flagV)
    {
      flags |= (uint8_t)(1 << 7);
    }

  if (m_flagI)
    {
      flags |= (uint8_t)(1 << 6);
    }

  if (m_flagD)
    {
      flags |= (uint8_t)(1 << 5);
    }

  i.WriteU8 (flags);
  i.WriteU8 (m_rplInstanceId);
  i.WriteU8 (m_versionNumber);
  m_dodagId.Serialize (buff_dodagId);
  i.Write (buff_dodagId, 16);
}

uint32_t RplSolicitedInformationOption::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buf[16];
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetLength (i.ReadU8 ());
  m_flags = i.ReadU8 ();
  m_rplInstanceId = i.ReadU8 ();
  m_versionNumber = i.ReadU8 ();
  i.Read (buf, 16);
  m_dodagId.Set (buf);

  return GetSerializedSize ();
}

}
