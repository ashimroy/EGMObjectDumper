# EGMObjectDumper
This package dumps electron and photon related variables into a flat tree. The package runs on CMS MINIAOD data/MC. Also it will be updated soon to run on AOD data/MC.

How to Install?

cmsrel CMSSW_11_1_0_pre8

cd CMSSW_11_1_0_pre8/src

cmsenv

git clone https://github.com/ashimroy/EGMObjectDumper

scram b -j8

cmsRun EGMObjectDumper/egmNtuplizer/python/ConfFile_cfg.py


How to submit CRAB jobs?

cd EGMObjectDumper/egmNtuplizer/test

source set_env.sh   ## It will ask for grid password.

python egmNtuple_CrabSubmit.py  ## You can edit this file on your requirement. 
