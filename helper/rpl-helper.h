/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef RPL_HELPER_H
#define RPL_HELPER_H

#include "ns3/rpl.h"
#include "ns3/object-factory.h"
#include "ns3/ipv6-routing-helper.h"
#include "ns3/node-container.h"
#include "ns3/node.h"
#include "ns3/rpl-option.h"
#include "ns3/rpl-metric.h"

namespace ns3 {

/**
 * \ingroup ipv6Helpers
 *
 * \brief Helper class that adds RPL routing to nodes.
 *
 */

class RplHelper: public Ipv6RoutingHelper
{
public:
  /*
   * Construct an RplHelper to make life easier while adding Rpl 
   * routing to nodes
   */

  RplHelper ();

  virtual ~RplHelper();

  /**
   * \returns pointer to clone of this RipNgHelper
   *
   * This method is mainly for internal use by the other helpers;
   * clients are expected to free the dynamic memory allocated by this method
   */
  RplHelper* Copy (void) const;

  /**
   * \param node the node on which the routing protocol will run
   * \returns a newly-created routing protocol
   *
   * This method will be called by ns3::InternetStackHelper::Install
   */
  virtual Ptr<Ipv6RoutingProtocol> Create (Ptr<Node> node) const;

  /**
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set.
   *
   * This method controls the attributes of ns3::Rpl
   */
  void Set (std::string name, const AttributeValue &value);

  /**
   * Assign a fixed random variable stream number to the random variables
   * used by this model. Return the number of streams (possibly zero) that
   * have been assigned. The Install() method should have previously been
   * called by the user.
   *
   * \param c NetDeviceContainer of the set of net devices for which the
   *          SixLowPanNetDevice should be modified to use a fixed stream
   * \param stream first stream index to use
   * \return the number of stream indices assigned by this helper
   */
  int64_t AssignStreams (NodeContainer c, int64_t stream);

  /**
   * \brief Install a default route in the node.
   *
   * The traffic will be routed to the nextHop, located on the specified
   * interface, unless a more specific route is found.
   *
   * \param node the node
   * \param nextHop the next hop
   * \param interface the network interface
   */
  void SetDefaultRouter (Ptr<Node> node, Ipv6Address nextHop, uint32_t interface);


private:
  /** the factory to create RPL routing object */
  ObjectFactory m_factory;



};

}

#endif /* RPL_HELPER_H */

