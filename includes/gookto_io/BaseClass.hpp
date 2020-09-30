#ifndef BASECLASS_H
#define BASECLASS_H
#include <vector>
typedef unsigned long long u_ll;

class MetadataBase{
    private:
        u_ll id;
        float _freeFlowSpeed, _max_spd,  _min_spd, _waveSpeed;
        float _length, _width, _Qmax;
        size_t _maxVehicle;
        
    public:
        MetadataBase() = default;
        
        MetadataBase(u_ll id_val){
            id = id_val;
        }
        MetadataBase(u_ll id_val, float length_val){
            id = id_val;
            _length = length_val;
        }
        MetadataBase(u_ll id_val, float length_val, float width_val){
            id = id_val;
            _length = length_val;
            _width = width_val;
        }
        MetadataBase(u_ll id_val, float length_val, float freeFlowSpeed_val, float max_spd_val, float  min_spd_val, float waveSpeed_val, size_t maxVehicle_val, float Qmax_val){
            id = id_val;
            _length = length_val;
            _freeFlowSpeed = freeFlowSpeed_val;
            _max_spd = max_spd_val;
            _min_spd = min_spd_val;
            _waveSpeed = waveSpeed_val;
            _maxVehicle = maxVehicle_val;
            _Qmax = Qmax_val;
            _width = -1;
        }
        ~MetadataBase() = default;
        MetadataBase(const MetadataBase& metadatabase) = default;
        MetadataBase& operator=(const MetadataBase& metadatabase) = default;


        // common for every other class
        void setID(u_ll id_val){id = id_val;}
        u_ll getID(){return id;}
        void setLength(float length_val){_length = length_val;}
        float getLength(){return _length;}
        void setWidth(float width_val){ _width = width_val;}
        float getWidth(){return _width;}


        // for link and cell 
        virtual void setFreeFlowSpeed(float val){ _freeFlowSpeed = val;}
        virtual void setQmax(float val){_Qmax = val;}
        virtual void setWaveSpeed(float val){ _waveSpeed = val;}
        virtual void setMaxVehicle(size_t val){_maxVehicle = val;}
        virtual void setMaxSpeed(float val){_max_spd = val;}
        virtual void setMinSpeed(float val){_min_spd = val;}

        
        virtual float getFreeFlowSpeed(){return _freeFlowSpeed;}
        virtual float getQmax(){return _Qmax;}
        virtual float getWaveSpeed(){return _waveSpeed;}
        virtual size_t getMaxVehicle(){return _maxVehicle;}
        virtual float getMaxSpeed(){return _max_spd;}
        virtual float getMinSpeed(){return _min_spd;}
};









#endif