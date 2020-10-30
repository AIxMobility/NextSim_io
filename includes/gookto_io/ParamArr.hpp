#pragma once
#include <vector>
#include <string>

class ParamArr
{
public:
    ParamArr();

    void SetMean(double val, const char* str);
    void SetSd(double val, const char* str);

    /*
    SetModel
    description: set Dist value to a specific number depending on the model

    Model --> Type #
    
    Normal       --> 1
    Lognormal    --> 2

     */

    void SetModel(const char* model, const char* str);

    void SetMaxFlow(double val) { max_flow = val; }
    void SetMesoVehLen(double val) { meso_veh_len = val; }
    void SetWaveSpeed(double val) { wave_speed = val; }

    //access functions
    [[nodiscard]] const std::vector<double>& GetMicroVehLen() const
    {
        return micro_veh_len;
    }

    [[nodiscard]] const std::vector<double>& GetJamGap() const
    {
        return jam_gap;
    }

    [[nodiscard]] const std::vector<double>& GetFFSpeed() const
    {
        return ff_speed;
    }

    [[nodiscard]] const std::vector<double>& GetReactionTime() const { return reaction_time; }
    [[nodiscard]] const std::vector<double>& GetMaxAcc() const { return max_acc; }
    [[nodiscard]] const std::vector<double>& GetMaxDec() const { return max_dec; }

    [[nodiscard]] double GetMaxFlow() const { return max_flow; }
    [[nodiscard]] double GetMesoVehLen() const { return meso_veh_len; }
    [[nodiscard]] double GetWaveSpeed() const { return wave_speed; }

private:
    // Micro Param
    std::vector<double> micro_veh_len;
    std::vector<double> jam_gap;
    std::vector<double> ff_speed;
    std::vector<double> reaction_time;
    std::vector<double> max_acc;
    std::vector<double> max_dec;

    // Meso Param
    double max_flow;
    double meso_veh_len;
    double wave_speed;
};
