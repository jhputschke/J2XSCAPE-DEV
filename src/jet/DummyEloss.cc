// -----------------------------------------
// JetScape (modular/task) based framework
// Intial Design: Joern Putschke (2017)
//                (Wayne State University)
// -----------------------------------------
// License and Doxygen-like Documentation to be added ...

// quick and dirty test class implementation for Eloss modules ...
// can be used as a user template ...

#include "DummyEloss.h"
#include "JetScapeLogger.h"
#include "JetScapeXML.h"
#include <string>
#include <thread>

#include "tinyxml2.h"
#include<iostream>
//#include "helper.h"

#include "FluidDynamics.h"

#define MAGENTA "\033[35m"

using namespace Jetscape;

DummyEloss::DummyEloss()
{
  SetId("DummyEloss");
  VERBOSE(8);
}

DummyEloss::~DummyEloss()
{
  VERBOSE(8);
}

void DummyEloss::Init()
{
  JSINFO<<"Intialize DummyEloss ...";

  // Initialize random number distribution
  ZeroOneDistribution = uniform_real_distribution<double> { 0.0, 1.0 };
}

void DummyEloss::DoEnergyLoss(double deltaT, double time, double Q2, vector<Parton>& pIn, vector<Parton>& pOut)
{

  VERBOSESHOWER(8)<< MAGENTA << "SentInPartons Signal received : "<<deltaT<<" "<<Q2<<" "<<&pIn;

  double rNum = ZeroOneDistribution(*GetMt19937Generator());

  //DEBUG:
  //cout<< rNum<<endl;

  if (rNum<0.1)
    {
      //DEBUG:
      JSDEBUG<<"My dummy Eloss module ..."<<time<<" "<<deltaT;//<<endl;
      //DEBUG<<"pIn : "<<pIn.front();//<<endl;

      //pOut.push_back(pIn.front());

      Parton pp=pIn.front();

      double x[4]={0,0,0,0};
      //Parton pNew(p.plabel(),p.pid(),p.pstat(),p.pt(),p.eta(),p.phi(),p.e(),x);
      double z=0.9;
      //double e=sqrt(p.pt()*z*p.pt()*z*cosh(p.eta())*cosh(p.eta())+p.m()*p.m());
      //double m=sqrt(p.e()*z*z*p.e()-p.pt()*z*p.pt()*z*cosh(p.eta())*cosh(p.eta()));
      //double pp=sqrt(p.e()*z*z*p.e()-p.m()*p.m());

      //cout<<pp<<" "<<p.pt()*z*cosh(p.eta())<<endl;
      //cout<<p.m()<<" "<<m<<endl;

      auto vp=pp.GetPseudoJet();
      fjcore::PseudoJet ve(0,0,0,0);
      ve.reset_PtYPhiM(pp.pt()*(1-z),pp.eta(),pp.phi(),0);

      auto p=vp-ve;

      Parton pNew(pp.plabel(),pp.pid(),pp.pstat(),p.pt(),p.eta(),p.phi(),p.e(),x);

      //cout<<pNew.pt()<<endl;
      //Parton (int label, int id, int stat, double pt, double eta, double phi, double e, double* x=0);
      //pOut.push_back(*std::make_shared<Parton>(p.plabel(),p.pid(),p.pstat(),p.pt(),p.eta(),p.phi(),p.e(),p.x_in()));

      pOut.push_back(pNew);


      //Parton pInNew(0,21,0,1,0,0,1,x);
      // Dummy test ... (works)
      //pIn.push_back(pInNew);

    }

  /*
  FluidCellInfo* check_fluid_info_ptr = new FluidCellInfo;
  if (time<0.3)
    DEBUGTHREAD<<std::this_thread::get_id()<<" | Memory : "<<this;
  GetHydroCellSignal(time, 1.0, 1.0, 0.0, check_fluid_info_ptr);
  VERBOSE(8)<< MAGENTA<<"Temperature from Brick (Signal) = "<<check_fluid_info_ptr->temperature;
  delete check_fluid_info_ptr;
  */
  /*
  double delT = deltaT;
  double Time = time*fmToGeVinv;
  double deltaTime = delT*fmToGeVinv;
  */
}
