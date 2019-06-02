#include "maxcpp6.h"
#include "softcut/SoftCut.h"
#include "softcut/Types.h"
#include "Utilities.h"

// inherit from the MSP base class, template-specialized for myself:

class Softcut_msp : public MspCpp6<Softcut_msp> {
public:
    
    enum { MaxBlockFrames = 2048, NumVoices = 6 };
    enum { BufFrames = 16777216 };
    
    softcut::SoftCut<NumVoices> cut;
    
    float buf[2][BufFrames];
    
    bool enabled[NumVoices];
    softcut::phase_t quantPhase[NumVoices];
    
    Softcut_msp(t_symbol * sym, long ac, t_atom * av) {
        setupIO(NumVoices, NumVoices);
        post("object dang created");
        
        for(int i=0; i<NumVoices; ++i) {
            cut.setVoiceBuffer(i, buf[i&1], BufFrames);
        }
    }
    
    ~Softcut_msp() {
        post("object freed");
    }
    
    // methods:
    void bang(long inlet) {
        post("bang in inlet %i!", inlet);
    }
    void test(long inlet, t_symbol * s, long ac, t_atom * av) {
        post("%s in inlet %i (%i args)", s->s_name, inlet, ac);
    }
    
    // default signal processing method is called 'perform'
    void perform(double **ins, long numins, double **outs, long numouts, long sampleframes) {
        // example code to invert inputs
        for (long v = 0; v < numouts; v++) {
            double * in = ins[v];
            double * out = outs[v];
            
            if (!enabled[v]) {
                continue;
            }
            
            cut.processBlock(v, (const float *) in, (float*) out, (int) sampleframes);
        }
    }
    
    //    void dsp(t_object * dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
    ////        REGISTER_PERFORM(T, perform);
    //
    //
    //    }
};

//void Softcut_msp::process(jack_nframes_t numFrames) {
//    Commands::softcutCommands.handlePending(this);
//    clearBusses(numFrames);
//    mixInput(numFrames);
//    // process softcuts (overwrites output bus)
//    for(int v=0; v<NumVoices; ++v) {
//        if (!enabled[v]) {
//            continue;
//        }
//        cut.processBlock(v, input[v].buf[0], output[v].buf[0], static_cast<int>(numFrames));
//    }
//    mixOutput(numFrames);
//    mix.copyTo(sink[0], numFrames);
//}
//
//void Softcut_msp::setSampleRate(jack_nframes_t sr) {
//    cut.setSampleRate(sr);
//}


//void Softcut_msp::clearBusses(size_t numFrames) {
//    mix.clear(numFrames);
//    for (auto &b : input) { b.clear(numFrames); }
//}

//void Softcut_msp::mixInput(size_t numFrames) {
//    for(int ch=0; ch<2; ++ch) {
//        for(int v=0; v<NumVoices; ++v) {
//            if(cut.getRecFlag(v)) {
//                input[v].mixFrom(&source[SourceAdc][ch], numFrames, inLevel[ch][v]);
//                for (int w = 0; w < NumVoices; ++w) {
//                    if(cut.getPlayFlag(w)) {
//                        input[v].mixFrom(output[w], numFrames, fbLevel[v][w]);
//                    }
//                }
//            }
//        }
//    }
//}

//void Softcut_msp::mixOutput(size_t numFrames) {
//    for(int v=0; v<NumVoices; ++v) {
//        if(cut.getPlayFlag(v)) {
//            mix.panMixFrom(output[v], numFrames, outLevel[v], outPan[v]);
//        }
//    }
//}

//void Softcut_msp::handleCommand(Commands::CommandPacket *p) {
//    switch(p->id) {
//            //-- softcut routing
//        case Commands::Id::SET_ENABLED_CUT:
//            std::cout << "softcut: setting enabled: voice "
//            << p->idx_0 << ": " << (p->value > 0) << std::endl;
//            enabled[p->idx_0] = p->value > 0.f;
//            break;
//        case Commands::Id::SET_LEVEL_CUT:
//            std::cout << "softcut: setting voice output level "
//            << p->idx_0 << ": " << p->value << std::endl;
//            outLevel[p->idx_0].setTarget(p->value);
//            break;;
//        case Commands::Id::SET_PAN_CUT:
//            outPan[p->idx_0].setTarget(p->value);
//            break;
//        case Commands::Id::SET_LEVEL_IN_CUT:
//            std::cout << "softcut: setting voice input level "
//            << p->idx_0 << ": " << p->idx_1 << ": " << p->value << std::endl;
//            inLevel[p->idx_0][p->idx_1].setTarget(p->value);
//            break;
//        case Commands::Id::SET_LEVEL_CUT_CUT:
//            fbLevel[p->idx_0][p->idx_1].setTarget(p->value);
//            break;
//            //-- softcut commands
//        case Commands::Id::SET_CUT_RATE:
//            cut.setRate(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_LOOP_START:
//            cut.setLoopStart(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_LOOP_END:
//            cut.setLoopEnd(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_LOOP_FLAG:
//            cut.setLoopFlag(p->idx_0, p->value > 0.f);
//            break;
//        case Commands::Id::SET_CUT_FADE_TIME:
//            cut.setFadeTime(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_REC_LEVEL:
//            cut.setRecLevel(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_PRE_LEVEL:
//            cut.setPreLevel(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_REC_FLAG:
//            cut.setRecFlag(p->idx_0, p->value > 0.f);
//            break;
//        case Commands::Id::SET_CUT_PLAY_FLAG:
//            cut.setPlayFlag(p->idx_0, p->value > 0.f);
//            break;
//        case Commands::Id::SET_CUT_REC_OFFSET:
//            cut.setRecOffset(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_POSITION:
//            cut.cutToPos(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_FC:
//            cut.setFilterFc(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_FC_MOD:
//            cut.setFilterFcMod(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_RQ:
//            cut.setFilterRq(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_LP:
//            cut.setFilterLp(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_HP:
//            cut.setFilterHp(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_BP:
//            cut.setFilterBp(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_BR:
//            cut.setFilterBr(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_FILTER_DRY:
//            cut.setFilterDry(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_LEVEL_SLEW_TIME:
//            cut.setLevelSlewTime(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_RATE_SLEW_TIME:
//            cut.setRateSlewTime(p->idx_0, p->value);
//            break;
//        case Commands::Id::SET_CUT_VOICE_SYNC:
//            cut.syncVoice(p->idx_0, p->idx_1, p->value);
//            break;
//        case Commands::Id::SET_CUT_BUFFER:
//            cut.setVoiceBuffer(p->idx_0, buf[p->idx_1], BufFrames);
//            break;
//        default:
//            ;;
//    }
//}

///////////////////
/// FIXME: DRY these all up


C74_EXPORT int main(void) {
    // create a class with the given name:
    Softcut_msp::makeMaxClass("softcut~");
    REGISTER_METHOD(Softcut_msp, bang);
    REGISTER_METHOD_GIMME(Softcut_msp, test);
}
