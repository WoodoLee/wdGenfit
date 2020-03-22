#include "TDatabasePDG.h"
#include "TPie.h"
#include "TPieSlice.h"
#include "TLegend.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TNtuple.h"
#include "TSystem.h"
#include "TEfficiency.h"
#include "TTree.h"
#include <AbsFinitePlane.h>
#include <AbsFitterInfo.h>
#include <AbsKalmanFitter.h>
#include <AbsMeasurement.h>
#include <AbsTrackRep.h>
#include <ConstField.h>
#include <DAF.h>
#include <DetPlane.h>
#include <EventDisplay.h>
#include <Exception.h>
#include <FieldManager.h>
#include <Fit/Fitter.h>
#include <FullMeasurement.h>
#include <GFGbl.h>
#include <HelixTrackModel.h>
#include <KalmanFitStatus.h>
#include <KalmanFittedStateOnPlane.h>
#include <KalmanFitter.h>
#include <KalmanFitterInfo.h>
#include <KalmanFitterRefTrack.h>
#include <MaterialEffects.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <MeasuredStateOnPlane.h>
#include <MeasurementCreator.h>
#include <MeasurementOnPlane.h>
#include <PlanarMeasurement.h>
#include <ProlateSpacepointMeasurement.h>
#include <RKTrackRep.h>
#include <RectangularFinitePlane.h>
#include <ReferenceStateOnPlane.h>
#include <SharedPlanePtr.h>
#include <SpacepointMeasurement.h>
#include <StateOnPlane.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TChain.h>
#include <TDatabasePDG.h>
#include <TEllipse.h>
#include <TEveManager.h>
#include <TF1.h>
#include <TF2.h>
#include <TFrame.h>
#include <TGeoManager.h>
#include <TGeoMaterialInterface.h>
#include <TGraph2D.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2F.h>
#include <TH2I.h>
#include <TH3F.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMarker.h>
#include <TMath.h>
#include <TPad.h>
#include <TPie.h>
#include <TPolyLine.h>
#include <TPolyLine3D.h>
#include <TPolyMarker.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TVector3.h>
#include <TVirtualPad.h>
#include <Tools.h>
#include <Track.h>
#include <TrackCand.h>
#include <TrackCandHit.h>
#include <TrackPoint.h>
#include <WireMeasurement.h>
#include <WirePointMeasurement.h>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace ROOT::Math;
using namespace std;
using namespace genfit;
using namespace RooFit;
int main()
{
  //Conditions
  double BZ = 30.;
  const int pdgWanted  = -11;  // particle pdg code -11 = positron
  //double pitch = 0.02;
  double pitch = 0.019;
  double resolution =  pitch ;
  gRandom->SetSeed(14);
  // init MeasurementCreator
  genfit::MeasurementCreator measurementCreator;
  // init geometry and mag. field
<<<<<<< HEAD
  TString fileData = "/home/wdlee/Work/build/geant4/g2wdsys_build/g2wd1M.root";
  TString fileGeom = "/home/wdlee/Work/build/geant4/g2wdsys_build/g2wdGeom.gdml";
=======
  TString fileData = "/home/wdlee/Work/build/geant4/g2wdPGsys_build/g2wd.root";
  TString fileGeom = "/home/wdlee/Work/build/geant4/g2wdPGsys_build/g2wdGeom.gdml";
>>>>>>> 90c36bf1128719ca813d626dfe0794dc56ad372a
  new TGeoManager("Geometry", "Geane geometry");
  TGeoManager::Import(fileGeom.Data());
  genfit::FieldManager::getInstance()->init(new genfit::ConstField(0.,0., BZ)); // BZ kGauss
  genfit::MaterialEffects *mateff = genfit::MaterialEffects::getInstance();
  mateff->setEnergyLossBrems(true);
  mateff->setNoiseBrems(true);
  mateff->setEnergyLossBetheBloch(true);
  mateff->setNoiseBetheBloch(true);
  mateff->setNoiseCoulomb(true);
  genfit::MaterialEffects::getInstance()->init(new genfit::TGeoMaterialInterface());
  // init event display
  genfit::EventDisplay* display = genfit::EventDisplay::getInstance();
  // init fitter
  //genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitterRefTrack();
  //genfit::AbsKalmanFitter* fitter = new genfit::KalmanFitter();
  genfit::AbsKalmanFitter* fitter = new genfit::DAF();
  //genfit::AbsKalmanFitter* fitter = new genfit::DAF(true, 1e-3, 1e-3);
  //const genfit::eFitterType fitter = genfit::DafRef;
  //const genfit::eFitterType fitterId = genfit::DafSimple;

  //GenFit options
  const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedAverage;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToReference;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPrediction;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedClosestToReference;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedClosestToPrediction;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToReferenceWire;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::unweightedClosestToPredictionWire;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedClosestToReferenceWire;
  //const genfit::eMultipleMeasurementHandling mmHandling = genfit::weightedClosestToPredictionWire;
  fitter->setMultipleMeasurementHandling(mmHandling);
  double dPVal(1.E-3);
  double  dRelChi2(0.2);
  //double  dChi2Ref(1.);
  double  nMinIter(3);
  double  nMaxIter(100);
  int nMaxFailed(-1);
  //bool refit(false);
  //bool  squareRootFormalism(false);

  fitter->setMinIterations(nMinIter);
  fitter->setMaxIterations(nMaxIter);
  fitter->setRelChi2Change(dRelChi2);
  fitter->setMaxFailedHits(nMaxFailed);

  TFile* f = new TFile("FittingResult.root","recreate");
  TTree *tr= new TTree("data", "data");
  
  double momInit, momFitted , momDiff, momRes;
  double firstHitX, firstHitY, firstHitZ, firstHitT; 
  tr -> Branch ("momInit",  &momInit , "momInit/D");
  tr -> Branch ("momFitted" ,  &momFitted  , "momFittied/D");
  tr -> Branch ("momDiff" ,  &momDiff  , "momDiff/D");
  tr -> Branch ("momRes" ,  &momRes  , "momRes/D");
  tr -> Branch ("firstHitX" ,  &firstHitX , "firstHitX/D");
  tr -> Branch ("firstHitY" ,  &firstHitY , "firstHitY/D");
  tr -> Branch ("firstHitZ" ,  &firstHitZ , "firstHitZ/D");
  tr -> Branch ("firstHitT" ,  &firstHitT , "firstHitT/D");
  
  TFile* file = new TFile(fileData.Data());
  std::cout << "\033[1;32m [Notice] File " << fileData.Data() << " is open.\033[0m" << std::endl;
  
  TTree *treeHit = (TTree*)(file->Get("Hit"));
  int hitEventID;
  double hitTime;
  double hitPosX,hitPosY, hitPosZ;
  double hitPMag;
  double hitPX, hitPY, hitPZ;
  double hitRA;
  double hitR;
  double eDep;
  double hitAngle;
  double VolID;
  treeHit -> SetBranchAddress("hitEventID",&hitEventID);
  treeHit -> SetBranchAddress("hitTime",&hitTime);
  treeHit -> SetBranchAddress("hitPosX",&hitPosX);
  treeHit -> SetBranchAddress("hitPosY",&hitPosY);
  treeHit -> SetBranchAddress("hitPosZ",&hitPosZ);
  treeHit -> SetBranchAddress("hitPX",&hitPX);
  treeHit -> SetBranchAddress("hitPY",&hitPY);
  treeHit -> SetBranchAddress("hitPZ",&hitPZ);
  treeHit -> SetBranchAddress("hitPMag",&hitPMag);
  treeHit -> SetBranchAddress("hitAngle",&hitAngle);
  treeHit -> SetBranchAddress("eDep",&eDep);
  treeHit -> SetBranchAddress("VolID",&VolID);
  vector < vector <double> > hitT;
  vector < vector <double> > hitX;
  vector < vector <double> > hitY;
  vector < vector <double> > hitZ;
  vector < vector <double> > momX;
  vector < vector <double> > momY;
  vector < vector <double> > momZ;
  hitT.clear();
  hitX.clear();
  hitY.clear();
  hitZ.clear();
  momX.clear();
  momY.clear();
  momZ.clear();
  vector <double> hitTTemp;
  vector <double> hitXTemp;
  vector <double> hitYTemp;
  vector <double> hitZTemp;
  vector <double> momXTemp;
  vector <double> momYTemp;
  vector <double> momZTemp;
  int preEid ;
  int postEid;
  int eIDhit = treeHit -> GetEntries();
  std::cout << "\033[1;32m [Notice] " << eIDhit << " number of Entries. \033[0m" << std::endl;
  
  for (int i = 0; i < eIDhit; i++)
  {
    //std::cout << "\033[1;32m [Notice] event [ " << i << " ] is being fitted \033[0m" << std::endl;
    treeHit -> GetEntry(i);
    preEid = hitEventID;
    hitTTemp.push_back(hitTime);
    hitXTemp.push_back(hitPosX);
    hitYTemp.push_back(hitPosY);
    hitZTemp.push_back(hitPosZ);
    momXTemp.push_back(hitPX);
    momYTemp.push_back(hitPY);
    momZTemp.push_back(hitPZ);
    treeHit -> GetEntry(i+1);
    postEid = hitEventID;
    //cout << "preEid = " << preEid << endl;
    //cout << "postEid = " << postEid << endl;
    //cout << "hitTime = " << hitTime << endl;
    if(preEid == eIDhit)
    {
      hitT.push_back(hitTTemp);
      hitX.push_back(hitXTemp);
      hitY.push_back(hitYTemp);
      hitZ.push_back(hitZTemp);
      momX.push_back(momXTemp);
      momY.push_back(momYTemp);
      momZ.push_back(momZTemp);
      hitTTemp.clear();
      hitXTemp.clear();
      hitYTemp.clear();
      hitZTemp.clear();
      momXTemp.clear();
      momYTemp.clear();
      momZTemp.clear();
    }
    if(preEid != postEid)
    {
      hitT.push_back(hitTTemp);
      hitX.push_back(hitXTemp);
      hitY.push_back(hitYTemp);
      hitZ.push_back(hitZTemp);
      momX.push_back(momXTemp);
      momY.push_back(momYTemp);
      momZ.push_back(momZTemp);
      hitTTemp.clear();
      hitXTemp.clear();
      hitYTemp.clear();
      hitZTemp.clear();
      momXTemp.clear();
      momYTemp.clear();
      momZTemp.clear();
    }
  }
  int trackN = hitX.size();
  //for (int i = 0; i < 10; i++)
  //{
  //  //std::cout << "\033[1;37m [Notice] Track [ " << i << " ]  \033[0m" << std::endl;
  //  for (int j = 0; j < hitX[i].size(); j++)
  //  {
  //    //std::cout << "\033[1;36m [Notice] hit  [ " << hitX[i][j] <<", " <<  hitY[i][j] << "," << hitZ[i][j]  << " ]  \033[0m" << std::endl;
  //  }
  //}
  
  // Looping over entries
  std::cout << "\033[1;31m [Notice] " << trackN << " number of Tracks. \033[0m" << std::endl;
  for ( int i = 0; i < trackN; i++ )
  //for ( int i = 0; i < 10; i++ )
  {
    if(i % 100 == 0)
    {
      std::cout << "\033[1;32m [Notice] track [ " << i << " ] is being fitted. \033[0m" << std::endl;
    }
    //Array for momentums
    //chekc the real Hit number ;
    //set the initial state(for Kalman filter step 0) Units: cm / GeV/c
    //std::cout << "\033[1;35m [Notice] Initial Condition [ " << i << " ] is being fitted. \033[0m" << std::endl;
    TVector3 pos( hitX[i][0] / 10.  , hitY[i][0] / 10.    , hitZ[i][0] / 10.  );
    TVector3 mom( momX[i][0] / 1000. , momY[i][0] / 1000.  , momZ[i][0] / 1000. );
    
    firstHitX = hitX[i][0];
    firstHitY = hitY[i][0];
    firstHitZ = hitZ[i][0];
    firstHitT = hitT[i][0];
    //pos.Print();
    //mom.Print();
    //Calculate the Magnitude of Initial momentum - will be use in Momentum cutting
    double momMag = mom.Mag();
    //mom.Print();
    const int pdg = pdgWanted ;     // particle pdg
    //const double charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/(3.);
    //genfit::HelixTrackModel* helix = new genfit::HelixTrackModel(pos, mom, charge);
    //measurementCreator.setTrackModel(helix);
    //get the charge : why devide by 3? - Curious(from Dasilva) 
    //const double charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/(3.);
    //std::cout << "charge  = " << charge << std::endl;
    // smeared start values
    //const bool smearPosMom = true;     // init the Reps with smeared pos and mom
    const bool smearPosMom = false;     // init the Reps with smeared pos and mom
    const double posSmear = 0.019;     // cm
    //const double momSmear = 3. /180.*TMath::Pi();     // rad
    const double momSmear = 0.019;     // rad
    //const double momMagSmear = 0.019;   // relative
    //hmomshit -> Fill( momMag* 1000. , countHits);
    TVector3 posM(pos);
    TVector3 momM(mom);
    if (smearPosMom)
    {
      posM.SetX(gRandom->Gaus(posM.X(),posSmear));
      posM.SetY(gRandom->Gaus(posM.Y(),posSmear));
      posM.SetZ(gRandom->Gaus(posM.Z(),posSmear));
      momM.SetX(gRandom->Gaus(momM.X(),momSmear));
      momM.SetY(gRandom->Gaus(momM.Y(),momSmear));
      momM.SetZ(gRandom->Gaus(momM.Z(),momSmear));
    }
    // approximate covariance(Kalman filter step.1)

    int nHits = hitX[i].size();
    //if (nHits ==0) continue;

    TMatrixDSym covM(6);
    for (int k = 0; k < 3; ++k)
    {
      covM(k,k) = resolution * resolution;
      //covM(k,k) = pow(posSmear,2);
    }
    for (int k = 3; k < 6; ++k)
    {
      covM(k,k) = pow(resolution / nHits / sqrt(3), 2);
    }
    // trackrep
    genfit::AbsTrackRep* rep = new genfit::RKTrackRep(pdg);
    // smeared start state
    genfit::MeasuredStateOnPlane stateSmeared(rep);
    stateSmeared.setPosMomCov(posM, momM, covM);
    genfit::MeasuredStateOnPlane stateRef(rep);
    stateRef.setPosMomCov(pos, mom, covM);
    // remember original initial state
    const genfit::StateOnPlane stateRefOrig(stateRef);
    // create track
    TVectorD seedState(6);
    TMatrixDSym seedCov(6);
    stateSmeared.get6DStateCov(seedState, seedCov);
    genfit::Track fitTrack(rep, seedState, seedCov);
    // create random measurement types
    TMatrixDSym hitCov(2);
    hitCov.UnitMatrix();
    hitCov *=resolution *resolution;
    //for (int j = 0; j < nHits; j++)
    for (int j = 0; j < 6; j++)
    {
      //pick the hit positions
      TVector3 cPos(hitX[i][j]/ 10. , hitY[i][j] / 10.  , hitZ[i][j] / 10. );
      //double cPer = cPos.Perp() ; 
      if(cPos == TVector3(0.,0.,0.)) continue;
      double phi = cPos.Phi();
      //double phi = cPos.Theta();
      TVector3 o(18.425 * TMath::Cos(phi), 18.425 * TMath::Sin(phi), 0.);
      TVector3 u(0., 0., 1. );
      TVector3 v = o.Unit();
      TVectorD hitCoords(2);
      hitCoords[0] = cPos.Z();
      hitCoords[1] = cPos.Perp() - 18.425;
      //std::cout << "\033[1;32m [Notice] cPos [ " << j << " ]  \033[0m" << std::endl;
      //cPos.Print();
      genfit::PlanarMeasurement * measurement = new genfit::PlanarMeasurement(hitCoords, hitCov, 0., j ,nullptr );
      measurement ->setPlane(genfit::SharedPlanePtr(new genfit::DetPlane(o,u,v) ), 0 );
      fitTrack.insertPoint(new genfit::TrackPoint(measurement,&fitTrack ));
    }
    
    // assert(fitTrack.checkConsistency());
    // do the fit
    fitTrack.checkConsistency();
    fitter->processTrack(&fitTrack);
    //display->addEvent(&fitTrack);
    if (i % 100 == 0)
    {
      std::cout << "\033[1;32m [Notice] Fitting track [ " << i << " ] is done. \033[0m" << std::endl;
    }

    genfit::TrackPoint* tp = fitTrack.getPointWithMeasurementAndFitterInfo(0, rep);
    if (tp == nullptr) continue;
    //genfit::KalmanFittedStateOnPlane kfsop(*(static_cast<genfit::KalmanFitterInfo*>(tp->getFitterInfo(rep))->getBackwardUpdate()));
      genfit::KalmanFittedStateOnPlane kfsop(*(static_cast<genfit::KalmanFitterInfo*>(tp->getFitterInfo(rep))->getForwardUpdate()));
      const TVectorD& referenceState = stateRefOrig.getState();
      const TVectorD& state = kfsop.getState();
      const TMatrixDSym covf = kfsop.getCov();
    //genfit::FitStatus *fitstat = fitTrack->getFitStatus(rep);
    //bool fitconv = fitstat->isFitConverged();
    //double chi2 = fitstat->getChi2();
    //double NDF = fitstat->getNdf();
    //fittedTrack->_chi2ndf = chi2/NDF;
    
    //if(!fitconv)
    //{
    //  cout << "Track could not be fitted successfully" << endl;
    //  delete fittedTrack;
    //  delete fitTrack;
    //  continue;
    //}
//
//    //genfit::TrackPoint* tp = fitTrack->getPointWithMeasurementAndFitterInfo(0, rep);
//    //if(tp==NULL){
//    //  cout << "Track has no TrackPoint with fitterInfo" << endl;
//    //  delete fittedTrack;
//    //  delete fitTrack;
//    //  continue;
    //}







    //genfit::FitStatus *fitstat = fitTrack.getFitStatus(rep);
    //bool fitconv = fitstat->isFitConverged();
    //if(!fitconv)
    //{
    //  //cout << "Track could not be fitted successfully" << endl;
    //  continue;
    //}

    momInit = (1./referenceState[0]) *  1000.; 
    momFitted = (1./state[0]) * 1000.; 
    momDiff = momInit - momFitted; 
    momRes = (momInit - momFitted) / momInit;
    tr -> Fill();
     //hmomResAllTest -> Fill(  momRes );
    //hmomDiffAllTest-> Fill( momDiff );
    //if (abs(momFitted) > 200 && abs(momFitted) < 275)
    //{  
    //  hmomResMomCutTest -> Fill(  momRes );
    //  hmomDiffMomCutTest ->Fill( momDiff);
//
//    //  if (abs(momRes) < 0.2 )
//    //  {
//    //    hmomResCutTest -> Fill(momRes);
//    //  }
//    //  if (abs(momDiff) < 0.2 * momInit)
//    //  {
//    //    hmomDiffCutTest -> Fill(momDiff);
//    //  }
    //}
  
    //double cutR  = 0.2;
    //for (int j = 0; j < window; j ++)
    //{
    //  if (j * windowRange < abs(momFitted) &&  abs(momFitted) < (j+1) * windowRange)
    //  {
    //    hmomRes[j]-> Fill( ((1./state[0]) - (1./referenceState[0] )) / (1./referenceState[0]));
    //    hmomDiff[j]-> Fill(  (1./state[0])*1000. - (1./referenceState[0] )*1000.);
    //    momSig[j] = hmomDiff[j] ->GetStdDev();
    //    double trueNTemp = 0.;
    //    double resTemp = 0.;
    //    resTemp = (( ( (1./state[0]) - (1./referenceState[0] )) / (1./referenceState[0])));
    //    double resMTemp = abs(resTemp);
    //    posiNum[j] = hmomRes[j] -> GetEntries();
    //    if(resMTemp < cutR )
    //    {
    //      hmomResCut[j]-> Fill( ((1./state[0]) - (1./referenceState[0] )) / (1./referenceState[0]));
    //      hmomDiffCut[j]-> Fill(  (1./state[0])*1000. - (1./referenceState[0] )*1000.);
    //      double fittedNTemp = 0.;
    //      fittedNTemp = hmomResCut[j] ->GetEntries();
    //      posiNumFit[j] = fittedNTemp;
    //      Eff[j] = (fittedNTemp / trueNTemp) * 100.;
    //    }
    //  }
    //}
 
  }
  f  -> cd();
  tr -> Write();   
  f  -> Close();
  
  delete fitter;
  //TCanvas* c1 = new TCanvas();
  //c1 -> Divide(2,3); 
  //c1 -> cd(1);
  //hmomResAllTest->Draw();
  //c1 -> cd(2);
  //hmomDiffAllTest->Draw();
  //c1 -> cd(3);
  //hmomResMomCutTest -> Draw();
  //c1 -> cd(4);
  //hmomDiffMomCutTest -> Draw();
  //c1 -> cd(5);
  //hmomResCutTest ->Draw();
  //c1 -> cd(6);
  //hmomDiffCutTest ->Draw();
  
  //TCanvas* c2 = new TCanvas();
  //c2 -> Divide(5,5);
  //for (int k=0; k < 10; k ++)
  //{
  //  c2 -> cd(k);
  //  hmomRes[k] -> Draw();
  //}
  
  //display->setOptions("ABDEFHMPT"); // G show geometry
  //display->open();


}
