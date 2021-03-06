#include "CondCore/PopCon/interface/PopConAnalyzer.h"
#include "CondTools/Hcal/interface/HcalQIEDataHandler.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//typedef popcon::PopConAnalyzer<HcalQIEDataHandler> HcalQIEDataPopConAnalyzer;

class HcalQIEDataPopConAnalyzer : public popcon::PopConAnalyzer<HcalQIEDataHandler> {
public:
  typedef HcalQIEDataHandler SourceHandler;

  HcalQIEDataPopConAnalyzer(const edm::ParameterSet& pset)
      : popcon::PopConAnalyzer<HcalQIEDataHandler>(pset),
        m_populator(pset),
        m_source(pset.getParameter<edm::ParameterSet>("Source")),
        m_tok(esConsumes<HcalQIEData, HcalQIEDataRcd>()) {}

private:
  void endJob() override {
    m_source.initObject(myDBObject);
    write();
  }

  void analyze(const edm::Event& ev, const edm::EventSetup& esetup) override {
    //Using ES to get the data:

    myDBObject = new HcalQIEData(esetup.getData(m_tok));
  }

  void write() { m_populator.write(m_source); }

private:
  popcon::PopCon m_populator;
  SourceHandler m_source;
  edm::ESGetToken<HcalQIEData, HcalQIEDataRcd> m_tok;

  HcalQIEData* myDBObject;
};

DEFINE_FWK_MODULE(HcalQIEDataPopConAnalyzer);
