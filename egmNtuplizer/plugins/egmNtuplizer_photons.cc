//
// Original Author:  Ashim Roy
//         Created:  Sat, 13 Jun 2020 20:37:58 GMT

#include "../interface/egmNtuplizer.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

using namespace std;
using namespace edm;

Int_t          nPho_;
vector<float>  phoE_;
vector<float>  phoEt_;
vector<float>  phoEta_;
vector<float>  phoPhi_;
vector<float>  phoSigmaE_;
vector<float>  phoCalibE_;
vector<float>  phoCalibEt_;
vector<float>  phoSCE_;
vector<float>  phoSCRawE_;
vector<float>  phoESEn_;
vector<float>  phoESEnP1_;
vector<float>  phoESEnP2_;
vector<float>  phoSCEta_;
vector<float>  phoSCPhi_;
vector<float>  phoSCEtaWidth_;
vector<float>  phoSCPhiWidth_;
vector<float>  phoSCBrem_;
vector<int>    phohasPixelSeed_;
vector<int>    phoEleVeto_;
vector<float>  phoR9_;
vector<float>  phoHoverE_;
vector<float>  phoESEffSigmaRR_;
vector<float>  phoSigmaIEtaIEtaFull5x5_;
vector<float>  phoSigmaIEtaIPhiFull5x5_;
vector<float>  phoSigmaIPhiIPhiFull5x5_;
vector<float>  phoE2x2Full5x5_;
vector<float>  phoE5x5Full5x5_;
vector<float>  phoR9Full5x5_;
vector<float>  phoPFChIso_;
vector<float>  phoPFChPVIso_;
vector<float>  phoPFPhoIso_;
vector<float>  phoPFNeuIso_;
vector<float>  phoPFChWorstVetoIso_;
vector<float>  phoPFChWorstIso_;
vector<float>  phoEcalPFClusterIso_;
vector<float>  phoHcalPFClusterIso_;
vector<float>  phoTrkIso_;
vector<float>  phoTrkSumPtSolidConeDR03_;
vector<float>  phoTrkSumPtHollowConeDR03_;
vector<float>  phoTrkSumPtSolidConeDR04_;
vector<float>  phoTrkSumPtHollowConeDR04_;

//vector<float>  phoSeedBCE_;
//vector<float>  phoSeedBCEta_;
vector<float>  phoIDMVA_;
vector<ULong64_t> phoFiredSingleTrgs_;
vector<ULong64_t> phoFiredDoubleTrgs_;
vector<ULong64_t> phoFiredTripleTrgs_;
vector<ULong64_t> phoFiredL1Trgs_;
vector<float>  phoSeedTime_;
vector<float>  phoSeedEnergy_;
vector<int>  phoSeediEta_;
vector<int>  phoSeediPhi_;
vector<vector<float>> phoEnergyMatrix5x5_;
vector<vector<float>> phoEnergyMatrix7x7_;
vector<vector<float>> phoEnergyMatrix9x9_;
vector<vector<float>> phoEnergyMatrix11x11_;
vector<vector<float>> phoEnergyMatrix15x15_;
vector<vector<float>> phoEnergyMatrix25x25_;

//Necessary for the Photon Footprint removal
template <class T, class U>
bool isInFootprint(const T& thefootprint, const U& theCandidate) {
  for ( auto itr = thefootprint.begin(); itr != thefootprint.end(); ++itr ) {

    if( itr.key() == theCandidate.key() ) return true;
    
  }
  return false;
}

void egmNtuplizer::branchesPhotons(TTree* tree) {

  //////////////////////////////Photon Branches/////////////////////////////////////////
  tree->Branch("nPho",                    &nPho_);
  tree->Branch("phoE",                    &phoE_);
  tree->Branch("phoEt",                   &phoEt_);
  tree->Branch("phoEta",                  &phoEta_);
  tree->Branch("phoPhi",                  &phoPhi_);
  //tree->Branch("phoSigmaE",               &phoSigmaE_);
  //tree->Branch("phoCalibE",               &phoCalibE_);
  //tree->Branch("phoCalibEt",              &phoCalibEt_);
  tree->Branch("phoSCE",                  &phoSCE_);
  tree->Branch("phoSCRawE",               &phoSCRawE_);
  tree->Branch("phoESEn",                 &phoESEn_);
  tree->Branch("phoESEnP1",               &phoESEnP1_);
  tree->Branch("phoESEnP2",               &phoESEnP2_);
  tree->Branch("phoSCEta",                &phoSCEta_);
  tree->Branch("phoSCPhi",                &phoSCPhi_);
  tree->Branch("phoSCEtaWidth",           &phoSCEtaWidth_);
  tree->Branch("phoSCPhiWidth",           &phoSCPhiWidth_);
  tree->Branch("phoSCBrem",               &phoSCBrem_);
  tree->Branch("phohasPixelSeed",         &phohasPixelSeed_);
  tree->Branch("phoEleVeto",              &phoEleVeto_);
  tree->Branch("phoR9",                   &phoR9_);
  tree->Branch("phoHoverE",               &phoHoverE_);
  tree->Branch("phoESEffSigmaRR",         &phoESEffSigmaRR_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIPhiFull5x5", &phoSigmaIEtaIPhiFull5x5_);
  tree->Branch("phoSigmaIPhiIPhiFull5x5", &phoSigmaIPhiIPhiFull5x5_);
  tree->Branch("phoE2x2Full5x5",          &phoE2x2Full5x5_);
  tree->Branch("phoE5x5Full5x5",          &phoE5x5Full5x5_);
  tree->Branch("phoR9Full5x5",            &phoR9Full5x5_);
  tree->Branch("phoPFChIso",              &phoPFChIso_);
  tree->Branch("phoPFChPVIso",            &phoPFChPVIso_);
  tree->Branch("phoPFPhoIso",             &phoPFPhoIso_);
  tree->Branch("phoPFNeuIso",             &phoPFNeuIso_);
  tree->Branch("phoPFChWorstIso",         &phoPFChWorstIso_);
  tree->Branch("phoPFChWorstVetoIso",     &phoPFChWorstVetoIso_);
  tree->Branch("phoEcalPFClusterIso",     &phoEcalPFClusterIso_);
  tree->Branch("phoHcalPFClusterIso",     &phoHcalPFClusterIso_);
  //tree->Branch("phoTrkIso",               &phoTrkIso_);
  tree->Branch("phoTrkSumPtSolidConeDR03", &phoTrkSumPtSolidConeDR03_);
  tree->Branch("phoTrkSumPtHollowConeDR03", &phoTrkSumPtHollowConeDR03_);
  tree->Branch("phoTrkSumPtSolidConeDR04", &phoTrkSumPtSolidConeDR04_);
  tree->Branch("phoTrkSumPtHollowConeDR04", &phoTrkSumPtHollowConeDR04_);
  
  tree->Branch("phoSeedTime",             &phoSeedTime_);
  tree->Branch("phoSeedEnergy",           &phoSeedEnergy_);
  tree->Branch("phoSeediEta",             &phoSeediEta_);
  tree->Branch("phoSeediPhi",             &phoSeediPhi_);
  tree->Branch("phoEnergyMatrix5x5",     &phoEnergyMatrix5x5_);
  tree->Branch("phoEnergyMatrix7x7",     &phoEnergyMatrix7x7_);
  tree->Branch("phoEnergyMatrix9x9",     &phoEnergyMatrix9x9_);
  tree->Branch("phoEnergyMatrix11x11",     &phoEnergyMatrix11x11_);
  tree->Branch("phoEnergyMatrix15x15",     &phoEnergyMatrix15x15_);
  tree->Branch("phoEnergyMatrix25x25",     &phoEnergyMatrix25x25_);

}

//
// member functions
//
// ------------ method called for each event  ------------
void egmNtuplizer::fillPhotons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  //////////////////////////////Cleaning of previous event/////////////////////////////////////////
  phoE_                   .clear();
  phoSigmaE_              .clear();
  phoEt_                  .clear();
  phoEta_                 .clear();
  phoPhi_                 .clear();
  phoCalibE_              .clear();
  phoCalibEt_             .clear();
  phoSCE_                 .clear();
  phoSCRawE_              .clear();
  phoESEn_                .clear();
  phoESEnP1_              .clear();
  phoESEnP2_              .clear();
  phoSCEta_               .clear();
  phoSCPhi_               .clear();
  phoSCEtaWidth_          .clear();
  phoSCPhiWidth_          .clear();
  phoSCBrem_              .clear();
  phohasPixelSeed_        .clear();
  phoEleVeto_             .clear();
  phoR9_                  .clear();
  phoHoverE_              .clear();
  phoESEffSigmaRR_        .clear();
  phoSigmaIEtaIEtaFull5x5_.clear();
  phoSigmaIEtaIPhiFull5x5_.clear();
  phoSigmaIPhiIPhiFull5x5_.clear();
  phoE2x2Full5x5_         .clear();
  phoE5x5Full5x5_         .clear();
  phoR9Full5x5_           .clear();
  phoPFChIso_             .clear();
  phoPFChPVIso_           .clear();
  phoPFPhoIso_            .clear();
  phoPFNeuIso_            .clear();
  phoPFChWorstVetoIso_    .clear();
  phoPFChWorstIso_        .clear();
  phoEcalPFClusterIso_    .clear();
  phoHcalPFClusterIso_    .clear();
  phoTrkIso_              .clear();
  phoTrkSumPtSolidConeDR03_.clear();
  phoTrkSumPtHollowConeDR03_.clear();
  phoTrkSumPtSolidConeDR04_.clear();
  phoTrkSumPtHollowConeDR04_.clear();
  
  phoSeedTime_            .clear();
  phoSeedEnergy_          .clear();
  phoSeediEta_            .clear();
  phoSeediPhi_            .clear();
  phoEnergyMatrix5x5_     .clear();
  phoEnergyMatrix7x7_     .clear();
  phoEnergyMatrix9x9_     .clear();
  phoEnergyMatrix11x11_   .clear();
  phoEnergyMatrix15x15_   .clear();
  phoEnergyMatrix25x25_   .clear();
  nPho_ = 0;

  //////////////////////////////Filling of Variables///////////////////////////////////
  edm::Handle<edm::View<pat::Photon> > photonHandle;
  iEvent.getByToken(photonCollection_, photonHandle);

  // Get the RecHits from the event
  Handle<EcalRecHitCollection> pRecHitsEB;
  iEvent.getByToken(ebReducedRecHitCollection_, pRecHitsEB);

  // Get the RecHits from the event
  Handle<EcalRecHitCollection> pRecHitsEE;
  iEvent.getByToken(eeReducedRecHitCollection_, pRecHitsEE);

  if (!photonHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Photons in event";
    return;
  }

  EcalClusterLazyTools       lazyTool    (iEvent, ecalClusterESGetTokens_.get(iSetup), ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  noZS::EcalClusterLazyTools lazyToolnoZS(iEvent, ecalClusterESGetTokens_.get(iSetup), ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {
    phoE_               .push_back(iPho->energy());
    phoEt_              .push_back(iPho->et());
    ////AR Requested UserFloat ecalEnergyPostCorr is not available! Possible UserFloats are: 
    ////AR  PhotonMVAEstimatorRun2Spring16NonTrigV1Values PhotonMVAEstimatorRunIIFall17v1p1Values PhotonMVAEstimatorRunIIFall17v2Values 
    //phoCalibE_          .push_back(iPho->userFloat("ecalEnergyPostCorr"));
    //phoCalibEt_         .push_back(iPho->et()*iPho->userFloat("ecalEnergyPostCorr")/iPho->energy());
    //phoSigmaE_          .push_back(iPho->userFloat("ecalEnergyErrPostCorr"));
    phoEta_             .push_back(iPho->eta());
    phoPhi_             .push_back(iPho->phi());
    phoSCE_             .push_back((*iPho).superCluster()->energy());
    phoSCRawE_          .push_back((*iPho).superCluster()->rawEnergy());
    phoESEn_            .push_back((*iPho).superCluster()->preshowerEnergy());
    phoESEnP1_          .push_back((*iPho).superCluster()->preshowerEnergyPlane1());
    phoESEnP2_          .push_back((*iPho).superCluster()->preshowerEnergyPlane2());
    phoSCEta_           .push_back((*iPho).superCluster()->eta());
    phoSCPhi_           .push_back((*iPho).superCluster()->phi());
    phoSCEtaWidth_      .push_back((*iPho).superCluster()->etaWidth());
    phoSCPhiWidth_      .push_back((*iPho).superCluster()->phiWidth());
    phoSCBrem_          .push_back((*iPho).superCluster()->phiWidth()/(*iPho).superCluster()->etaWidth());
    phohasPixelSeed_    .push_back((Int_t)iPho->hasPixelSeed());
    phoEleVeto_         .push_back((Int_t)iPho->passElectronVeto());
    phoR9_              .push_back(iPho->r9());
    phoHoverE_          .push_back(iPho->hadTowOverEm());
    phoESEffSigmaRR_    .push_back(lazyTool.eseffsirir(*((*iPho).superCluster())));
    phoSigmaIEtaIEtaFull5x5_ .push_back(iPho->full5x5_sigmaIetaIeta());
    phoSigmaIEtaIPhiFull5x5_ .push_back(iPho->full5x5_showerShapeVariables().sigmaIetaIphi);
    phoSigmaIPhiIPhiFull5x5_ .push_back(iPho->full5x5_showerShapeVariables().sigmaIphiIphi);
    phoE2x2Full5x5_          .push_back(lazyToolnoZS.e2x2(*((*iPho).superCluster()->seed())));
    phoE5x5Full5x5_          .push_back(iPho->full5x5_e5x5());
    phoR9Full5x5_            .push_back(iPho->full5x5_r9());    
    phoPFChIso_         .push_back(iPho->chargedHadronIso()); //charged hadron isolation with dxy,dz match to pv
    phoPFChPVIso_       .push_back(iPho->chargedHadronPFPVIso()); //only considers particles assigned to the primary vertex (PV) by particle flow, corresponds to <10_6 chargedHadronIso
    phoPFPhoIso_        .push_back(iPho->photonIso());
    phoPFNeuIso_        .push_back(iPho->neutralHadronIso());
    phoPFChWorstIso_    .push_back(iPho->chargedHadronWorstVtxIso()); //max charged hadron isolation when dxy/dz matching to given vtx
    phoPFChWorstVetoIso_.push_back(iPho->chargedHadronWorstVtxGeomVetoIso()); //as chargedHadronWorstVtxIso but an additional geometry based veto cone
    phoEcalPFClusterIso_.push_back(iPho->ecalPFClusterIso());
    phoHcalPFClusterIso_.push_back(iPho->hcalPFClusterIso());
    phoTrkIso_          .push_back(iPho->trackIso());  // Returns the summed Et in a cone of deltaR<0.4 or trkSumPtSolidConeDR04
    phoTrkSumPtSolidConeDR03_.push_back(iPho->trkSumPtSolidConeDR03());
    phoTrkSumPtHollowConeDR03_.push_back(iPho->trkSumPtHollowConeDR03());
    phoTrkSumPtSolidConeDR04_.push_back(iPho->trkSumPtSolidConeDR04());
    phoTrkSumPtHollowConeDR04_.push_back(iPho->trkSumPtHollowConeDR04());
    
    const auto &seedSC = *(iPho->superCluster()->seed());
    DetId seedDetId = (iPho->superCluster()->seed()->hitsAndFractions())[0].first;
    bool isBarrel = seedDetId.subdetId() == EcalBarrel;
    
    const EcalRecHitCollection& rechits = (isBarrel? *pRecHitsEB : *pRecHitsEE); 
    EcalRecHitCollection::const_iterator theSeedHit = rechits.find(seedDetId);
    if (theSeedHit != rechits.end()) {
      //std::cout<<"(*theSeedHit).time()"<<(*theSeedHit).time()<<"seed energy: "<<(*theSeedHit).energy()<<std::endl;  

      phoSeedTime_  .push_back((*theSeedHit).time());
      phoSeedEnergy_.push_back((*theSeedHit).energy());
      if (isBarrel) {
	EBDetId det = theSeedHit->id();
	phoSeediEta_  .push_back(det.ieta());
	phoSeediPhi_  .push_back(det.iphi());
      }
      else {
	EEDetId det = theSeedHit->id();
	phoSeediEta_  .push_back(det.ix());
	phoSeediPhi_  .push_back(det.iy());
      }

    } else{
      phoSeedTime_  .push_back(-99.);
      phoSeedEnergy_.push_back(-99.);
      phoSeediEta_  .push_back(-999);
      phoSeediPhi_  .push_back(-999);
    }

    phoEnergyMatrix5x5_.push_back(lazyToolnoZS.energyMatrix(seedSC,2));
    phoEnergyMatrix7x7_.push_back(lazyToolnoZS.energyMatrix(seedSC,3));
    phoEnergyMatrix9x9_.push_back(lazyToolnoZS.energyMatrix(seedSC,4));
    phoEnergyMatrix11x11_.push_back(lazyToolnoZS.energyMatrix(seedSC,5));
    phoEnergyMatrix15x15_.push_back(lazyToolnoZS.energyMatrix(seedSC,7));
    phoEnergyMatrix25x25_.push_back(lazyToolnoZS.energyMatrix(seedSC,12));
    
    nPho_++;
  }

}
