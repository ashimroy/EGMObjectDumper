import sys
import CRABClient
from CRABClient.UserUtilities import config

config = config()

submitVersion = "ntuples_Run3Winter22_2021_v1"
mainOutputDir = '/store/group/phys_egamma/asroy/ID/Run3/egmNtuples/%s' % submitVersion

# Name of the CMSSW configuration file
config.JobType.psetName  = '/afs/cern.ch/work/a/asroy/public/EGammaWork/ID/EGMTree/CMSSW_12_2_1/src/EGMObjectDumper/egmNtuplizer/test/Run3_ConfFile_cfg.py'


config.General.transferLogs = False
config.JobType.pluginName  = 'Analysis'
config.JobType.sendExternalFolder = True
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True
config.Data.inputDBS = 'global'
config.Data.publication = False
#config.Data.publishDataName = 
config.Site.storageSite = 'T2_CH_CERN'
config.General.workArea = 'crab_%s' % submitVersion

##### now submit DATA
config.Data.outLFNDirBase = '%s/%s/' % (mainOutputDir,'data')
config.Data.splitting     = 'LumiBased'
config.Data.totalUnits      = -1
#config.Data.lumiMask      = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt' #UL2018  
config.Data.unitsPerJob   = 40


### For different DataSets
config.General.requestName = 'job_GJet_Pt-40toInf_DoubleEMEnriched_Run3Winter22_2021'
config.Data.inputDataset   = '/GJet_Pt-40toInf_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Winter22MiniAOD-FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM'

#config.General.requestName = 'job_GJet_Pt-10to40_DoubleEMEnriched_Run3Winter22_2021'
#config.Data.inputDataset   = '/GJet_Pt-10to40_DoubleEMEnriched_TuneCP5_13p6TeV_pythia8/Run3Winter22MiniAOD-FlatPU0to70_122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM'



