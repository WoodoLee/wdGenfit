# GenFit2 for g-2/edm experiment Package with g2track

  
   GenFit2 is popular package for particle fitting in HEP. This is fitting package for g-2/edm experiment at J-parc.   
  g2track is in this package. 
  
  
* Unit
  
  length = [cm]  
  Momentum = [GeV/c]  

* Data
    
  in data folder   

  testIn.root  : Output data from detectorsimulation (geant4 simulation)  
  testOut.root : Reconstructed data from g2track package. (10k muon simulation with geant4)  
  Detector.root: Detector structure from detectorsimulation.   

* How to build?  
    
  cmake .  
  make   
  make tests  
    
* How to run?  
    
  in bin folder  
  ./genfitg2 

* What i get?
  
  momentum resolution histogram
  
Original GenFit Homepage: (https://github.com/GenFit/GenFit)
