/**
 * @file DmpContextualTwoStep.hpp
 * @brief  Contextual Dmp class header file.
 * @author Freek Stulp
 *
 * This file is part of DmpBbo, a set of libraries and programs for the 
 * black-box optimization of dynamical movement primitives.
 * Copyright (C) 2014 Freek Stulp, ENSTA-ParisTech
 * 
 * DmpBbo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * DmpBbo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DmpBbo.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DMP_CONTEXTUAL_TWO_STEP_H_
#define _DMP_CONTEXTUAL_TWO_STEP_H_

#include "dmp/DmpContextual.hpp"

#include <set>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>



namespace DmpBbo {

class FunctionApproximator;
class FunctionApproximatorLWR;

/** 
 * \brief Implementation of Contextual Dynamical Movement Primitives.
 * \ingroup DmpContextual
 */
class DmpContextualTwoStep : public DmpContextual
{
public:
  
  /**
   *  Initialization constructor for Contextual DMPs of known dimensionality, but with unknown
   *  initial and attractor states. Initializes the DMP with default dynamical systems.
   *  \param n_dims_dmp      Dimensionality of the DMP
   *  \param function_approximators Function approximators for the forcing term
   *  \param policy_parameter_function Function approximators for the policy parameter function
   *  \param dmp_type  The type of DMP, see Dmp::DmpType    
   */
  DmpContextualTwoStep(int n_dims_dmp, std::vector<FunctionApproximator*> function_approximators, FunctionApproximator* policy_parameter_function, DmpType dmp_type=KULVICIUS_2012_JOINING);
  
  // Overloads Dmp::computeFunctionApproximatorOutput
  void computeFunctionApproximatorOutput(
    const Eigen::Ref<const Eigen::MatrixXd>& phase_state, Eigen::MatrixXd& fa_output) const;

  // Overloads Dmp::train
  void  train(const std::vector<Trajectory>& trajectories, const std::vector<Eigen::MatrixXd>& task_parameters, std::string save_directory="", bool overwrite = true);
  
  /** Return whether the DMP is trained or not.
   * \return true if the DMP is trained, false otherwise 
   */
  bool isTrained(void) const;

  
private:
  std::vector<std::vector<FunctionApproximator*> > policy_parameter_function_;

protected:
  /**
   * Default constructor.
   * \remarks This default constuctor is required for boost::serialization to work. See \ref sec_boost_serialization_ugliness
   */
   DmpContextualTwoStep(void) {}; 
   
private:
  /** Give boost serialization access to private members. */  
  friend class boost::serialization::access;
  
  /** Serialize class data members to boost archive. 
   * \param[in] ar Boost archive
   * \param[in] version Version of the class
   * \see page_serialization
   */
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(DmpContextual);
    ar & BOOST_SERIALIZATION_NVP(policy_parameter_function_);
  }
    

};

}


#endif