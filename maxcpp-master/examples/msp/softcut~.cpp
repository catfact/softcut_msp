#include "maxcpp6.h"
#include "softcut/SoftCut.h"
#include "softcut/Types.h"
#include "Utilities.h"

class Softcut_msp : public MspCpp6<Softcut_msp> {
public:
    
    enum { MaxBlockFrames = 2048, NumVoices = 6 };
    enum { BufFrames = 16777216 };
    
    softcut::SoftCut<NumVoices> cut;
    
    float buf[NumVoices][BufFrames];
    
    bool enabled[NumVoices];
    softcut::phase_t quantPhase[NumVoices];
    
    Softcut_msp(t_symbol * sym, long ac, t_atom * av) {
        
        listout((t_object *)this);
        
        post("softcut created");
        
//        clearBuffer();
        
        for(int i=0; i<NumVoices; ++i) {
            cut.setVoiceBuffer(i, buf[i], BufFrames);
        }
        
        cut.setSampleRate(441000);
        
        setupIO(NumVoices, NumVoices);
    }
    
    ~Softcut_msp() {
        post("object freed");
    }
    
//    void clearBuffer() {
//        for(int v=0; v < NumVoices; v++) {
//            for(int f=0; f < BufFrames; f++) {
//                buf[v][f] = 0.f;
//            }
//        }
//    }
    
    void filter_fc(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterFc(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_fc_mod(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterFcMod(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_rq(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterRq(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_lp(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterLp(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_hp(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterHp(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_bp(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterBp(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_br(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterBr(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void filter_dry(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFilterDry(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void pre_fade_window(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setPreFadeWindow(atom_getfloat(av));
    }
    
    void rec_fade_delay(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRecFadeDelay(atom_getfloat(av));
    }
    
    void pre_fade_shape(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setPreFadeShape(atom_getfloat(av));
    }
    
    void rec_fade_shape(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRecFadeShape(atom_getfloat(av));
    }
    
    void rate(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRate(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void play(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setPlayFlag(atom_getlong(av), atom_getfloat(av + 1) > 0.f);
    }
    void position(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.cutToPos(atom_getlong(av), atom_getfloat(av + 1));
    }
    void fade_time(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setFadeTime(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void loop(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setLoopFlag(atom_getlong(av), atom_getfloat(av + 1) > 0.f);
    }
    void loop_start(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setLoopStart(atom_getlong(av), atom_getfloat(av + 1));
    }
    void loop_end(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setLoopEnd(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void rec(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRecFlag(atom_getlong(av), atom_getfloat(av + 1) > 0.f);
    }
    void rec_level(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRecLevel(atom_getlong(av), atom_getfloat(av + 1));
    }
    void pre_level(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setPreLevel(atom_getlong(av), atom_getfloat(av + 1));
    }
    void rec_offset(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRecOffset(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void voice_sync(long inlet, t_symbol * s, long ac, t_atom * av) { //(src,dst,value)
        cut.syncVoice(atom_getlong(av), atom_getlong(av + 1), atom_getfloat(av + 2));
    }
    
    void level_slew_time(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setLevelSlewTime(atom_getlong(av), atom_getfloat(av + 1));
    }
    void rate_slew_time(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,val)
        cut.setRateSlewTime(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    void buffer(long inlet, t_symbol * s, long ac, t_atom * av) { //(voice,index)
        cut.setVoiceBuffer(atom_getlong(av), buf[atom_getlong(av + 1)], BufFrames);
    }
    
    void sample_rate(long inlet, t_symbol * s, long ac, t_atom * av) {
        cut.setVoiceSampleRate(atom_getlong(av), atom_getfloat(av + 1));
    }
    
    // default signal processing method is called 'perform'
    void perform(double **ins, long numins, double **outs, long numouts, long sampleframes) {
        // example code to invert inputs
        for (long v = 0; v < numouts; v++) {
            double * in = ins[v];
            double * out = outs[v];
            
//            if (!enabled[v]) {
//                continue;
//            }
            
            cut.processBlock(v, (const float *) in, (float*) out, (int) sampleframes);
        }
    }
    
//    void dsp(t_object * dsp64, short *count, double samplerate, long maxvectorsize, long flags) {
//        REGISTER_PERFORM(Softcut_msp, perform);
//
//        post("samplerate: %i", 441000);
//
//        cut.setSampleRate(441000);
//    }
};

C74_EXPORT int main(void) {
    Softcut_msp::makeMaxClass("softcut~");
    
    REGISTER_METHOD_GIMME(Softcut_msp, filter_fc);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_fc_mod);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_rq);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_lp);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_hp);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_bp);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_br);
    REGISTER_METHOD_GIMME(Softcut_msp, filter_dry);
    REGISTER_METHOD_GIMME(Softcut_msp, pre_fade_window);
    REGISTER_METHOD_GIMME(Softcut_msp, rec_fade_delay);
    REGISTER_METHOD_GIMME(Softcut_msp, pre_fade_shape);
    REGISTER_METHOD_GIMME(Softcut_msp, rec_fade_shape);
    REGISTER_METHOD_GIMME(Softcut_msp, rate);
    REGISTER_METHOD_GIMME(Softcut_msp, play);
    REGISTER_METHOD_GIMME(Softcut_msp, position);
    REGISTER_METHOD_GIMME(Softcut_msp, fade_time);
    REGISTER_METHOD_GIMME(Softcut_msp, loop);
    REGISTER_METHOD_GIMME(Softcut_msp, loop_start);
    REGISTER_METHOD_GIMME(Softcut_msp, loop_end);
    REGISTER_METHOD_GIMME(Softcut_msp, rec);
    REGISTER_METHOD_GIMME(Softcut_msp, rec_level);
    REGISTER_METHOD_GIMME(Softcut_msp, pre_level);
    REGISTER_METHOD_GIMME(Softcut_msp, rec_offset);
    REGISTER_METHOD_GIMME(Softcut_msp, voice_sync);
    REGISTER_METHOD_GIMME(Softcut_msp, level_slew_time);
    REGISTER_METHOD_GIMME(Softcut_msp, rate_slew_time);
    REGISTER_METHOD_GIMME(Softcut_msp, buffer);
    REGISTER_METHOD_GIMME(Softcut_msp, sample_rate);
}
