#include "ns3/header.h"
#include "ns3/ipv6-address.h"   
#include "ns3/log.h"
#include "rpl-header.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplHeader");

NS_OBJECT_ENSURE_REGISTERED(RplDisMessage);

TypeId RplDisMessage::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplDisMessage")
    .SetParent<Icmpv6Header> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplDisMessage> ()
  ;
  return tid;
}

TypeId RplDisMessage::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

RplDisMessage::RplDisMessage()
{
  NS_LOG_FUNCTION (this);
  SetType (155);
  SetCode (0);
  SetFlags (0);
  SetReserved (0);
}

RplDisMessage::~RplDisMessage ()
{
  NS_LOG_FUNCTION(this);
}

void RplDisMessage::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " (Rpl) code = " << (uint32_t)GetCode () << " checksum = " << (uint32_t)GetChecksum () << ")";
}

uint32_t RplDisMessage::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 6; //Not including options.

}
void RplDisMessage::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  i.WriteU8 (GetType ());
  i.WriteU8 (GetCode ());
  i.WriteU8 (m_flags);
  i.WriteU8 (m_reserved);
  //i.WriteU8 (m_options);
  //Still have to include options, haven't checked bytes yet.

}

uint32_t RplDisMessage::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  SetType (i.ReadU8 ());
  SetCode (i.ReadU8 ());
  m_flags = i.ReadU8 ();
  m_reserved = i.ReadU8 ();
  //m_options = i.ReadU8 ();

  return GetSerializedSize();
}

uint8_t RplDisMessage::GetFlags () const
{
  NS_LOG_FUNCTION(this);
  return m_flags;
}

void RplDisMessage::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION(this << f);
  m_flags = f;
}

uint8_t RplDisMessage::GetReserved () const
{
  NS_LOG_FUNCTION(this);
  return m_reserved;
}


void RplDisMessage::SetReserved (uint8_t reserved)
{
  NS_LOG_FUNCTION(this << reserved);
  m_reserved = reserved;
}

/*
*  \brief (DIO Base Object) Format
   \verbatim
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  | RPLInstanceID |Version Number |              Rank             |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |G|0| MOP | Prf |      DTSN     |    Flags    |     Reserved    |
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

NS_OBJECT_ENSURE_REGISTERED(RplDioMessage);

TypeId RplDioMessage::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplDioMessage")
    .SetParent<Icmpv6Header> ()
    .SetGroupName ("rpl")
    .AddConstructor<RplDioMessage> ()
  ;
  return tid;
}

TypeId RplDioMessage::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

RplDioMessage::RplDioMessage()
{
  NS_LOG_FUNCTION (this);
  SetType (155);
  SetCode (1);
  SetFlags (0);
  SetFlagG (0);
  SetReserved (0);
  SetDtsn (0);
  SetVersionNumber(0);
  SetRplInstanceId(0);
  SetRank(0);
  SetMop(0);
  SetPrf(0);
}

RplDioMessage::~RplDioMessage ()
{
  NS_LOG_FUNCTION(this);
}

void RplDioMessage::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " (Rpl) code = " << (uint32_t)GetCode () << " checksum = " << (uint32_t)GetChecksum () << ")";
}

uint32_t RplDioMessage::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 28; //Not including options.
}
void RplDioMessage::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buff_dodagId[16];
  Buffer::Iterator i = start;

  i.WriteU8 (GetType ());
  i.WriteU8 (GetCode ());

  i.WriteU8 (m_flags);
  i.WriteU8 (m_reserved);
  i.WriteU8 (m_dtsn);
  i.WriteU8 (m_versionNumber);
  i.WriteU8 (m_rplInstanceId);
  i.WriteU16 (m_rank);
  i.WriteU8 (m_mop);
  i.WriteU8 (m_prf);
  m_dodagId.Serialize (buff_dodagId);
  i.Write (buff_dodagId, 16);

  //Ground flag not serialized and deserialized
  //i.WriteU8 (m_options);
  //Still have to include options, haven't checked bytes yet.

}

uint32_t RplDioMessage::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buf[16];
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetCode (i.ReadU8 ());
  m_flags = i.ReadU8 ();
  m_reserved = i.ReadU8 ();
  m_dtsn = i.ReadU8 ();
  m_versionNumber = i.ReadU8 ();
  m_rplInstanceId = i.ReadU8 ();
  m_rank = i.ReadU16 ();
  m_mop = i.ReadU8 ();
  m_prf = i.ReadU8 ();
  i.Read (buf, 16);
  m_dodagId.Set (buf);

  return GetSerializedSize();
}

bool RplDioMessage::GetFlagG () const
{
  NS_LOG_FUNCTION(this);
  return m_flagG;
}

void RplDioMessage::SetFlagG (bool g)
{
  NS_LOG_FUNCTION(this << g);
  m_flagG = g;
}

uint8_t RplDioMessage::GetFlags () const
{
  NS_LOG_FUNCTION(this);
  return m_flags;
}

void RplDioMessage::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION(this << f);
  m_flags = f;
}

uint8_t RplDioMessage::GetMop () const
{
  NS_LOG_FUNCTION(this);
  return m_mop;
}

void RplDioMessage::SetMop (uint8_t mop)
{
  NS_LOG_FUNCTION(this << mop);
  m_mop = mop;
}

uint8_t RplDioMessage::GetPrf () const
{
  NS_LOG_FUNCTION(this);
  return m_prf;
}

void RplDioMessage::SetPrf (uint8_t prf)
{
  NS_LOG_FUNCTION(this << prf);
  m_prf = prf;
}

uint8_t RplDioMessage::GetRplInstanceId () const
{
  NS_LOG_FUNCTION(this);
  return m_rplInstanceId;
}

void RplDioMessage::SetRplInstanceId (uint8_t rplinstanceid)
{
  NS_LOG_FUNCTION(this << rplinstanceid);
  m_rplInstanceId = rplinstanceid;
}

uint8_t RplDioMessage::GetReserved () const
{
  NS_LOG_FUNCTION(this);
  return m_reserved;
}

void RplDioMessage::SetReserved (uint8_t reserved)
{
  NS_LOG_FUNCTION(this << reserved);
  m_reserved = reserved;
}

uint8_t RplDioMessage::GetDtsn () const
{
  NS_LOG_FUNCTION(this);
  return m_dtsn;
}

void RplDioMessage::SetDtsn (uint8_t dtsn)
{
  NS_LOG_FUNCTION(this << dtsn);
  m_dtsn = dtsn;
}

uint8_t RplDioMessage::GetVersionNumber () const
{
  NS_LOG_FUNCTION(this);
  return m_versionNumber;
}

void RplDioMessage::SetVersionNumber (uint8_t version)
{
  NS_LOG_FUNCTION(this << version);
  m_versionNumber = version;
}

uint16_t RplDioMessage::GetRank () const
{
  NS_LOG_FUNCTION(this);
  return m_rank;
}

void RplDioMessage::SetRank (uint16_t rank)
{
  NS_LOG_FUNCTION(this << rank);
  m_rank = rank;
}

Ipv6Address RplDioMessage::GetDodagId () const
{
  NS_LOG_FUNCTION(this);
  return m_dodagId;
}

void RplDioMessage::SetDodagId (Ipv6Address dodagId)
{
  NS_LOG_FUNCTION(this << dodagId);
  m_dodagId = dodagId;
}



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


NS_OBJECT_ENSURE_REGISTERED(RplDaoMessage);

TypeId RplDaoMessage::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplDaoMessage")
    .SetParent<Icmpv6Header> ()
    .SetGroupName ("rpl")
    .AddConstructor<RplDaoMessage> ()
  ;
  return tid;
}

TypeId RplDaoMessage::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

RplDaoMessage::RplDaoMessage()
{
  NS_LOG_FUNCTION (this);
  SetType (155);
  SetCode (2);
  SetFlags (0);
  SetFlagK (0);
  SetFlagD (0);
  SetReserved (0);
  SetDaoSequence(0);
  SetRplInstanceId(0);
}

RplDaoMessage::~RplDaoMessage ()
{
  NS_LOG_FUNCTION(this);
}

void RplDaoMessage::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " (Rpl) code = " << (uint32_t)GetCode () << " checksum = " << (uint32_t)GetChecksum () << ")";
}

uint32_t RplDaoMessage::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 24; //Not including options.
}

void RplDaoMessage::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buff_dodagId[16];
  Buffer::Iterator i = start;
  uint8_t flags = 0;


  i.WriteU8 (GetType ());
  i.WriteU8 (GetCode ());

  if (m_flagK)
    {
      flags |= (uint8_t)(1 << 7);
    }

  if (m_flagD)
    {
      flags |= (uint8_t)(1 << 6);
    }


  i.WriteU8 (flags);
  i.WriteU8 (m_reserved);
  i.WriteU8 (m_daoSequence);
  i.WriteU8 (m_rplInstanceId);
  m_dodagId.Serialize (buff_dodagId);
  i.Write (buff_dodagId, 16);
  //Write flag bits one by one
  //Search how to write 16 bytes for DODAGID
  //i.WriteU8 (m_options);
  //Still have to include options, haven't checked bytes yet.
}

uint32_t RplDaoMessage::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buf[16];
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetCode (i.ReadU8 ());
  m_flags = i.ReadU8 ();
  m_reserved = i.ReadU8 ();
  m_daoSequence = i.ReadU8 ();
  m_rplInstanceId = i.ReadU8 ();
  i.Read (buf, 16);
  m_dodagId.Set (buf);


  //m_options = i.ReadU8 ();

  return GetSerializedSize();
}


bool RplDaoMessage::GetFlagK () const
{
  NS_LOG_FUNCTION(this);
  return m_flagK;
}

void RplDaoMessage::SetFlagK (bool k)
{
  NS_LOG_FUNCTION(this << k);
  m_flagK = k;
}

bool RplDaoMessage::GetFlagD () const
{
  NS_LOG_FUNCTION(this);
  return m_flagD;
}

void RplDaoMessage::SetFlagD (bool d)
{
  NS_LOG_FUNCTION(this << d);
  m_flagD = d;
}

uint8_t RplDaoMessage::GetFlags () const
{
  NS_LOG_FUNCTION(this);
  return m_flags;
}

void RplDaoMessage::SetFlags (uint8_t f)
{
  NS_LOG_FUNCTION(this << f);
  m_flags = f;
}

uint8_t RplDaoMessage::GetRplInstanceId () const
{
  NS_LOG_FUNCTION(this);
  return m_rplInstanceId;
}

void RplDaoMessage::SetRplInstanceId (uint8_t rplinstanceid)
{
  NS_LOG_FUNCTION(this << rplinstanceid);
  m_rplInstanceId = rplinstanceid;
}

uint8_t RplDaoMessage::GetReserved () const
{
  NS_LOG_FUNCTION(this);
  return m_reserved;
}

void RplDaoMessage::SetReserved (uint8_t reserved)
{
  NS_LOG_FUNCTION(this << reserved);
  m_reserved = reserved;
}

uint8_t RplDaoMessage::GetDaoSequence () const
{
  NS_LOG_FUNCTION(this);
  return m_daoSequence;
}


void RplDaoMessage::SetDaoSequence (uint8_t sequence)
{
  NS_LOG_FUNCTION(this << sequence);
  m_daoSequence = sequence;
}

Ipv6Address RplDaoMessage::GetDodagId () const
{
  NS_LOG_FUNCTION(this);
  return m_dodagId;
}

void RplDaoMessage::SetDodagId (Ipv6Address dodagId)
{
  NS_LOG_FUNCTION(this << dodagId);
  m_dodagId = dodagId;

}


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


NS_OBJECT_ENSURE_REGISTERED(RplDaoAckMessage);

TypeId RplDaoAckMessage::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplDaoAckMessage")
    .SetParent<Icmpv6Header> ()
    .SetGroupName ("rpl")
    .AddConstructor<RplDaoAckMessage> ()
  ;
  return tid;
}

TypeId RplDaoAckMessage::GetInstanceTypeId () const
{
  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}

RplDaoAckMessage::RplDaoAckMessage()
{
  NS_LOG_FUNCTION (this);
  SetType (155);
  SetCode (3);
  SetStatus (0);
  SetFlagD (0);
  SetReserved (0);
  SetDaoSequence(0);
  SetRplInstanceId(0);
}

RplDaoAckMessage::~RplDaoAckMessage ()
{
  NS_LOG_FUNCTION(this);
}

void RplDaoAckMessage::Print (std::ostream& os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "( type = " << (uint32_t)GetType () << " (Rpl) code = " << (uint32_t)GetCode () << " checksum = " << (uint32_t)GetChecksum () << ")";
}

uint32_t RplDaoAckMessage::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return 24; //Not including options.
}

void RplDaoAckMessage::Serialize (Buffer::Iterator start) const
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buff_dodagId[16];
  Buffer::Iterator i = start;
  uint8_t flags = 0; //reserved field


  i.WriteU8 (GetType ());
  i.WriteU8 (GetCode ());

  if (m_flagD)
    {
      flags |= (uint8_t)(1 << 7);
    }


  i.WriteU8 (flags);
  i.WriteU8 (m_status);
  i.WriteU8 (m_daoSequence);
  i.WriteU8 (m_rplInstanceId);
  m_dodagId.Serialize (buff_dodagId);
  i.Write (buff_dodagId, 16);
}

uint32_t RplDaoAckMessage::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  uint8_t buf[16];
  Buffer::Iterator i = start;

  SetType (i.ReadU8 ());
  SetCode (i.ReadU8 ());
  m_reserved = i.ReadU8 ();
  m_status = i.ReadU8 ();
  m_daoSequence = i.ReadU8 ();
  m_rplInstanceId = i.ReadU8 ();
  i.Read (buf, 16);
  m_dodagId.Set (buf);


  return GetSerializedSize();
}

bool RplDaoAckMessage::GetFlagD () const
{
  NS_LOG_FUNCTION(this);
  return m_flagD;
}

void RplDaoAckMessage::SetFlagD (bool d)
{
  NS_LOG_FUNCTION(this << d);
  m_flagD = d;
}

uint8_t RplDaoAckMessage::GetRplInstanceId () const
{
  NS_LOG_FUNCTION(this);
  return m_rplInstanceId;
}

void RplDaoAckMessage::SetRplInstanceId (uint8_t rplinstanceid)
{
  NS_LOG_FUNCTION(this << rplinstanceid);
  m_rplInstanceId = rplinstanceid;
}

uint8_t RplDaoAckMessage::GetStatus () const
{
  NS_LOG_FUNCTION(this);
  return m_status;
}

void RplDaoAckMessage::SetStatus (uint8_t status)
{
  NS_LOG_FUNCTION(this << status);
  m_status = status;
}


uint8_t RplDaoAckMessage::GetReserved () const
{
  NS_LOG_FUNCTION(this);
  return m_reserved;
}

void RplDaoAckMessage::SetReserved (uint8_t reserved)
{
  NS_LOG_FUNCTION(this << reserved);
  m_reserved = reserved;
}

uint8_t RplDaoAckMessage::GetDaoSequence () const
{
  NS_LOG_FUNCTION(this);
  return m_daoSequence;
}


void RplDaoAckMessage::SetDaoSequence (uint8_t sequence)
{
  NS_LOG_FUNCTION(this << sequence);
  m_daoSequence = sequence;
}

Ipv6Address RplDaoAckMessage::GetDodagId () const
{
  NS_LOG_FUNCTION(this);
  return m_dodagId;
}

void RplDaoAckMessage::SetDodagId (Ipv6Address dodagId)
{
  NS_LOG_FUNCTION(this << dodagId);
  m_dodagId = dodagId;

}

}
