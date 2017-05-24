
#ifndef RPL_OBJECTIVE_FUNCTION_H
#define RPL_OBJECTIVE_FUNCTION_H

#include <stdint.h> 
#include <ns3/log.h>

namespace ns3 {

class RplObjectiveFunction
{
public:
  
  /**
   * \brief Constructor.
   */
  RplObjectiveFunction (void);

  /**
   * \brief Destructor.
   */
  ~RplObjectiveFunction ();
  
  /**
   * \brief Compute the rank
   * \param parentRank the rank of the preferred parent
   */
  static uint16_t ComputeRank (uint16_t parentRank);

};

class RplObjectiveFunctionOf0 : public RplObjectiveFunction
{
public:                                                                                                   
  /**
   * \brief Constructor.
   */
  RplObjectiveFunctionOf0 (void);

  /**
   * \brief Destructor.
   */
  ~RplObjectiveFunctionOf0 ();
  
  /**
   * \brief Compute the rank
   * \param parentRank the rank of the preferred parent
   */
  static uint16_t ComputeRank (uint16_t parentRank);

};

class RplObjectiveFunctionMhrof : public RplObjectiveFunction
{
public:                                                                                                   
  /**
   * \brief Constructor.
   */
  RplObjectiveFunctionMhrof (void);

  /**
   * \brief Destructor.
   */
  ~RplObjectiveFunctionMhrof ();
  
  /**
   * \brief Compute the rank
   * \param parentRank the rank of the preferred parent
   */
  static uint16_t ComputeRank (uint8_t metric);

};

}
#endif /* RPL_OBJECTIVE_FUNCTION_H */