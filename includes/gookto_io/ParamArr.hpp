#pragma once
#include <vector>
#include <string>

class ParamArr
{
private:
    //Micro Param
    std::vector<float> micro_veh_len;
    std::vector<float> jam_gap;
    std::vector<float> ff_speed;
    std::vector<float> reaction_time;
    std::vector<float> max_acc;
    std::vector<float> max_dec;

    //Meso Param
    float max_flow;
    float meso_veh_len;
    float wave_speed;

public:
    ParamArr();

    void setMean(float val, const char *str);
    void setSd(float val, const char *str);

    /*
    setModel
    description: set Dist value to a specific number depending on the model

    Model --> Type #
    
    Normal       --> 1
    Lognormal    --> 2

     */

    void setModel(const char *model, const char *str);

    void setMaxFlow(float val) { max_flow = val; }
    void setMesoVehLen(float val) { meso_veh_len = val; }
    void setWaveSpeed(float val) { wave_speed = val; }

    //access functions
    std::vector<float> getMicroVehLen() { return micro_veh_len; }
    std::vector<float> getJamGap() { return jam_gap; }
    std::vector<float> getFFSpeed() { return ff_speed; }
    std::vector<float> getReactionTime() { return reaction_time; }
    std::vector<float> getMaxAcc() { return max_acc; }
    std::vector<float> getMaxDec() { return max_dec; }

    float getMaxFlow() { return max_flow; }
    float getMesoVehLen() { return meso_veh_len; }
    float getWaveSpeed() {return wave_speed; }
};