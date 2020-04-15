/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <queue>
#include <map>
#include <assert.h>
#include <cstring>
#include <functional>
#include <memory>


namespace roc
{
	// exchange internal code
	// market,machine,plant,server,and so on
	enum {
		DUKAS,
		OANDA,
		CNEX,
		EX_0,  // numeric id  
		EX_1,
		EX_2,
		EX_3,
		NUM_EXCHANGE
	};
#define NUMERIC_ID_EXCHANGE_BASE  EX_0
#define NUM_NAMED_EXCHANGE  EX_0

	// instrument internal code
	// asset,sensor,and so on  
	enum {
		EURUSD,
		USDJPY,
		EURCHF,
		USDCHF,
		EURJPY,
		EURGBP,
		GBPUSD,
		GBPCHF,
		CHFJPY,
		AUDCHF,
		AUDNZD,
		USDCAD,
		AUDCAD,
		AUDJPY,
		AUDUSD,
		CADCHF,
		CADJPY,
		EURAUD,
		EURCAD,
		EURNZD,
		GBPAUD,
		GBPCAD,
		GBPJPY,
		GBPNZD,
		NZDCAD,
		NZDCHF,
		NZDJPY,
		NZDUSD,
		IN_0, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, IN_7, IN_8, IN_9,
		IN_10, IN_11, IN_12, IN_13, IN_14, IN_15, IN_16, IN_17, IN_18, IN_19,
		IN_20, IN_21, IN_22, IN_23, IN_24, IN_25, IN_26, IN_27, IN_28, IN_29,
		IN_30, IN_31, IN_32, IN_33, IN_34, IN_35, IN_36, IN_37, IN_38, IN_39,
		IN_40, IN_41, IN_42, IN_43, IN_44, IN_45, IN_46, IN_47, IN_48, IN_49,
		IN_50, IN_51, IN_52, IN_53, IN_54, IN_55, IN_56, IN_57, IN_58, IN_59,
		IN_60, IN_61, IN_62, IN_63, IN_64, IN_65, IN_66, IN_67, IN_68, IN_69,
		IN_70, IN_71, IN_72, IN_73, IN_74, IN_75, IN_76, IN_77, IN_78, IN_79,
		IN_80, IN_81, IN_82, IN_83, IN_84, IN_85, IN_86, IN_87, IN_88, IN_89,
		IN_90, IN_91, IN_92, IN_93, IN_94, IN_95, IN_96, IN_97, IN_98, IN_99,
#if 0  // reserved	
		IN_100, IN_101, IN_102, IN_103, IN_104, IN_105, IN_106, IN_107, IN_108, IN_109,
		IN_110, IN_111, IN_112, IN_113, IN_114, IN_115, IN_116, IN_117, IN_118, IN_119,
		IN_120, IN_121, IN_122, IN_123, IN_124, IN_125, IN_126, IN_127, IN_128, IN_129,
		IN_130, IN_131, IN_132, IN_133, IN_134, IN_135, IN_136, IN_137, IN_138, IN_139,
		IN_140, IN_141, IN_142, IN_143, IN_144, IN_145, IN_146, IN_147, IN_148, IN_149,
		IN_150, IN_151, IN_152, IN_153, IN_154, IN_155, IN_156, IN_157, IN_158, IN_159,
		IN_160, IN_161, IN_162, IN_163, IN_164, IN_165, IN_166, IN_167, IN_168, IN_169,
		IN_170, IN_171, IN_172, IN_173, IN_174, IN_175, IN_176, IN_177, IN_178, IN_179,
		IN_180, IN_181, IN_182, IN_183, IN_184, IN_185, IN_186, IN_187, IN_188, IN_189,
		IN_190, IN_191, IN_192, IN_193, IN_194, IN_195, IN_196, IN_197, IN_198, IN_199,
		IN_200, IN_201, IN_202, IN_203, IN_204, IN_205, IN_206, IN_207, IN_208, IN_209,
		IN_210, IN_211, IN_212, IN_213, IN_214, IN_215, IN_216, IN_217, IN_218, IN_219,
		IN_220, IN_221, IN_222, IN_223, IN_224, IN_225, IN_226, IN_227, IN_228, IN_229,
		IN_230, IN_231, IN_232, IN_233, IN_234, IN_235, IN_236, IN_237, IN_238, IN_239,
		IN_240, IN_241, IN_242, IN_243, IN_244, IN_245, IN_246, IN_247, IN_248, IN_249,
		IN_250, IN_251, IN_252, IN_253, IN_254, IN_255, IN_256, IN_257, IN_258, IN_259,
		IN_260, IN_261, IN_262, IN_263, IN_264, IN_265, IN_266, IN_267, IN_268, IN_269,
		IN_270, IN_271, IN_272, IN_273, IN_274, IN_275, IN_276, IN_277, IN_278, IN_279,
		IN_280, IN_281, IN_282, IN_283, IN_284, IN_285, IN_286, IN_287, IN_288, IN_289,
		IN_290, IN_291, IN_292, IN_293, IN_294, IN_295, IN_296, IN_297, IN_298, IN_299,
		IN_300, IN_301, IN_302, IN_303, IN_304, IN_305, IN_306, IN_307, IN_308, IN_309,
		IN_310, IN_311, IN_312, IN_313, IN_314, IN_315, IN_316, IN_317, IN_318, IN_319,
		IN_320, IN_321, IN_322, IN_323, IN_324, IN_325, IN_326, IN_327, IN_328, IN_329,
		IN_330, IN_331, IN_332, IN_333, IN_334, IN_335, IN_336, IN_337, IN_338, IN_339,
		IN_340, IN_341, IN_342, IN_343, IN_344, IN_345, IN_346, IN_347, IN_348, IN_349,
		IN_350, IN_351, IN_352, IN_353, IN_354, IN_355, IN_356, IN_357, IN_358, IN_359,
		IN_360, IN_361, IN_362, IN_363, IN_364, IN_365, IN_366, IN_367, IN_368, IN_369,
		IN_370, IN_371, IN_372, IN_373, IN_374, IN_375, IN_376, IN_377, IN_378, IN_379,
		IN_380, IN_381, IN_382, IN_383, IN_384, IN_385, IN_386, IN_387, IN_388, IN_389,
		IN_390, IN_391, IN_392, IN_393, IN_394, IN_395, IN_396, IN_397, IN_398, IN_399,
		IN_400, IN_401, IN_402, IN_403, IN_404, IN_405, IN_406, IN_407, IN_408, IN_409,
		IN_410, IN_411, IN_412, IN_413, IN_414, IN_415, IN_416, IN_417, IN_418, IN_419,
		IN_420, IN_421, IN_422, IN_423, IN_424, IN_425, IN_426, IN_427, IN_428, IN_429,
		IN_430, IN_431, IN_432, IN_433, IN_434, IN_435, IN_436, IN_437, IN_438, IN_439,
		IN_440, IN_441, IN_442, IN_443, IN_444, IN_445, IN_446, IN_447, IN_448, IN_449,
		IN_450, IN_451, IN_452, IN_453, IN_454, IN_455, IN_456, IN_457, IN_458, IN_459,
		IN_460, IN_461, IN_462, IN_463, IN_464, IN_465, IN_466, IN_467, IN_468, IN_469,
		IN_470, IN_471, IN_472, IN_473, IN_474, IN_475, IN_476, IN_477, IN_478, IN_479,
		IN_480, IN_481, IN_482, IN_483, IN_484, IN_485, IN_486, IN_487, IN_488, IN_489,
		IN_490, IN_491, IN_492, IN_493, IN_494, IN_495, IN_496, IN_497, IN_498, IN_499,
#endif	
		NUM_INSTRUMENT
	};
#define NUMERIC_ID_INSTRUMENTE_BASE  IN_0
#define NUM_NAMED_INSTRUMENT  IN_0


	// compressed data 
	enum TIMEFRAME {
		MSEC1,
		MSEC10,
		MSEC20,
		MSEC50,
		MSEC100,
		MSEC200,
		MSEC500,
		SEC1,
		SEC2,
		SEC5,
		SEC10,
		SEC15,
		SEC30,
		MIN1,
		MIN5,
		MIN15,
		MIN30,
		HOUR1,
		HOUR4,
		DAY,
		// The followings do not have interval time in usec
		WEEK,
		MONTH,
		QUARTER,
		YEAR,
		NUM_TIMEFRAME,
		TICK,
		NUM_TIMEFRAME_AND_TICK
	};
	typedef  unsigned long long  TIMEVAL;

	enum DATA_ELEM_TYPE {
		DE_EdgeData_IoT,
		DE_EdgeDataDouble_IoT,
		DE_TOHLCV_IoT,
		DE_TickData,	
		DE_TOHLCV,
		DE_Numeric,			// float, double, int
		DE_EdgeData_IoT_not_syncronized_array,
		DE_EdgeDataDouble_IoT_not_syncronized_array,
		DE_TOHLCV_IoT_not_syncronized_array,
		DE_TickData_not_syncronized_array,
		DE_TOHLCV_not_syncronized_array,
		DE_Numeric_not_syncronized_array,	// float, double, int
		NUM_DATA_ELEM_TYPEUM
	};
#define NOT_SYNCRONIZED_ARRAY_BASE DE_EdgeData_IoT_not_syncronized_array

	class ArrayDataBase {
	public:
		ArrayDataBase() :series_length(0), current_bar(-1), calculated_bars(0) {}

		virtual ~ArrayDataBase(void) {}
		int32_t   series_length;	// is series_length. don't use if 0   
		int32_t   current_bar;		// the current bar position ( 0,1,2,... )
		int32_t	  calculated_bars;	// number of calculated bars
	};

	//#pragma pack(push,4)
	
	struct EdgeData_IoT {
		uint64_t	tval;			// tval.sec is 0 if empty,     usec_since_epoch
		float       value[1];		// number of values is  _iot_de_count() of InInfo
		// ....... 
	};

	struct EdgeDataDouble_IoT {
		uint64_t	tval;			// tval.sec is 0 if empty,     usec_since_epoch
		double      value[1];		// number of values is  _iot_de_count() of InInfo
		// ....... 
	};

	struct OHLCV_IoT {
		float	open;
		float	high;
		float	low;
		float	close;
		float   vol;
	};

	struct TOHLCV_IoT {				// bar of the first value
		uint64_t tval_open;			// usec_since_epoch
		OHLCV_IoT ohlcv[1];
		// .....
	};

	struct TickData {
		uint64_t	tval;			// tval.sec is 0 if empty,     usec_since_epoch
		float		asks_price;
		float		asks_liquidity;
		float		bids_price;
		float		bids_liquidity;
	};

	struct TOHLCV { // TOHLCV is (ask + bid)/2
		uint64_t tval_open;		// usec_since_epoch
		float	open;
		float	high;
		float	low;
		float	close;
		float	vol;
		//  the followings are compressed by ticks
		float	bid_vol;
		uint32_t open_tick_bar;
		float	dollar_vol;
		float	bid_dollar_vol;
		float	force;
	};
	// #pragma pack(pop)

class UserMemoryDBBaseIF;



struct TfInfoIF {
public:
	virtual ~TfInfoIF(void) = default;
	TfInfoIF(void) {}
	// getter
	virtual int exchange() = 0;
	virtual int instrument() = 0;
	virtual int timeframe() = 0;

	virtual int _series_length() = 0;
	virtual int _current_bar() = 0;
	virtual int _start_bar() = 0;
	virtual int _calculated_bars() = 0;
	virtual UserMemoryDBBaseIF* _user_memory_db() = 0;
	virtual DATA_ELEM_TYPE _de_type() = 0;
	virtual TOHLCV* _tohlcv() = 0;
	virtual TickData* _tick() = 0;
	virtual TOHLCV_IoT* _tohlcv_iot() = 0;
	virtual EdgeData_IoT* _edge_data_iot() = 0;
	virtual EdgeDataDouble_IoT* _edge_data_double_iot() = 0;
	virtual int	_iot_de_count() = 0;
	virtual int	_iot_rec_size() = 0;

	// setter
	virtual void setDataElemType(DATA_ELEM_TYPE de_type_) = 0;
	virtual void setUserMemoryDb(UserMemoryDBBaseIF* user_mem_db) = 0;
	virtual void initTimeSeries(int series_length_, DATA_ELEM_TYPE de_type_, int iot_de_count_ = 0) = 0;

};

/**
*	User defined memory accessor interfaces
*/
class UserMemoryDBBaseIF {
  public:
	virtual ~UserMemoryDBBaseIF(void) = default;
	UserMemoryDBBaseIF(void) {}
};

// DATA_ELEM_TYPE is DE_Numeric or DE_Numeric_not_syncronized_array
class FloatArrayDataIF {
public:
	virtual ~FloatArrayDataIF() = default;
	FloatArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0; 
	//virtual void init_nan(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	virtual void set(int32_t i, float value) = 0;
	
	virtual float operator[] (int32_t i) = 0;   // access to the i-th value
	virtual float* barData(int32_t pos) = 0;   // access to the bar value

};

// DATA_ELEM_TYPE is DE_Numeric or DE_Numeric_not_syncronized_array
class DoubleArrayDataIF {
public:
	virtual ~DoubleArrayDataIF() = default;
	DoubleArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	//virtual void init_nan(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	virtual void set(int32_t i, double value) = 0;
	
	virtual double operator[] (int32_t i) = 0;   // access to the i-th value
	virtual double* barData(int32_t pos) = 0;   // access to the bar value
};

// DATA_ELEM_TYPE is DE_Numeric or DE_Numeric_not_syncronized_array
class IntArrayDataIF {
public:
	virtual ~IntArrayDataIF() = default;
	IntArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	virtual void set(int32_t i, int value) = 0;
	
	virtual int operator[] (int32_t i) = 0;   // access to the i-th value
	virtual int* barData(int32_t pos) = 0;   // access to the bar value
};

class EdgeDataIoTArrayDataIF {
public:
	virtual ~EdgeDataIoTArrayDataIF() = default;
	EdgeDataIoTArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true) = 0;
	virtual void setIoT(int32_t i, EdgeData_IoT* value) = 0;
	
	virtual EdgeData_IoT *operator[] (int32_t i) = 0;   // access to the i-th value
	virtual EdgeData_IoT *barData(int32_t pos) = 0;   // access to the bar value
};

class EdgeDataDoubleIoTArrayDataIF {
public:
	virtual ~EdgeDataDoubleIoTArrayDataIF() = default;
	EdgeDataDoubleIoTArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true) = 0;
	virtual void setIoT(int32_t i, EdgeDataDouble_IoT* value) = 0;
	
	virtual EdgeDataDouble_IoT* operator[] (int32_t i) = 0;   // access to the i-th value
	virtual EdgeDataDouble_IoT* barData(int32_t pos) = 0;   // access to the bar value
};

class TOHLCVIoTArrayDataIF {
public:
	virtual ~TOHLCVIoTArrayDataIF() = default;
	TOHLCVIoTArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true) = 0;
	virtual void setIoT(int32_t i, TOHLCV_IoT *value) = 0;
	
	virtual TOHLCV_IoT* operator[] (int32_t i) = 0;   // access to the i-th value
	virtual TOHLCV_IoT* barData(int32_t pos) = 0;   // access to the bar value
};

class TickDataArrayDataIF {
public:
	virtual ~TickDataArrayDataIF() = default;
	TickDataArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	virtual void set(int32_t i, TickData value) = 0;
	
	virtual TickData operator[] (int32_t i) = 0;   // access to the i-th value
	virtual TickData *barData(int32_t pos) = 0;   // access to the bar value
};

class TOHLCVArrayDataIF {
public:
	virtual ~TOHLCVArrayDataIF() = default;
	TOHLCVArrayDataIF(void) {}
	
	virtual void init(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true) = 0;
	virtual void set(int32_t i, TOHLCV value) = 0;
	
	virtual TOHLCV operator[] (int32_t i) = 0;   // access to the i-th value
	virtual TOHLCV* barData(int32_t pos) = 0;   // access to the bar value
};


/**
*	Platform time series accessor interfaces
*/
extern TfInfoIF* getTfInfo(int ex, int in, int tf);

class TickAccessorIF {
public:
	virtual ~TickAccessorIF() = default;
	TickAccessorIF() {}
	
	virtual TickData &operator[] (int32_t i) = 0;   // access to the i-th value
};

class TOHLCVAccessorIF {
public:
	virtual ~TOHLCVAccessorIF() = default;
	TOHLCVAccessorIF() {}
	
	virtual TOHLCV& operator[] (int32_t i) = 0;   // access to the i-th value
};

class TimeAccessorIF {
public:
	virtual ~TimeAccessorIF() = default;
	TimeAccessorIF() {}
	
	virtual TIMEVAL operator[] (int32_t i) = 0;   // access to the i-th value
};

class EdgeDataIoTAccessorIF {
public:
	virtual ~EdgeDataIoTAccessorIF() = default;
	EdgeDataIoTAccessorIF() {}

	virtual EdgeData_IoT* operator[] (int32_t i) = 0;   // access to the i-th value
	virtual EdgeData_IoT* barData(int32_t pos) = 0;   // access to the bar value

};

class EdgeDataDoubleIoTAccessorIF {
public:
	virtual ~EdgeDataDoubleIoTAccessorIF() = default;
	EdgeDataDoubleIoTAccessorIF() {}

	virtual EdgeDataDouble_IoT* operator[] (int32_t i) = 0;   // access to the i-th value
	virtual EdgeDataDouble_IoT* barData(int32_t pos) = 0;   // access to the bar value
};

/**
*	Directional Change interfaces
*/
enum class DC_DIRECTION : int {
	GOES_UP   = 1,
	GOES_DOWN = -1
};

enum class DC_EXTREAM : int {
	UPPER = 1, 
	LOWER = -1
};

struct DirectionalChangeInfoIF {
	virtual ~DirectionalChangeInfoIF() = default;
	DirectionalChangeInfoIF(void) {}
	// properties
	virtual DC_DIRECTION _dc_event_type() = 0;	// 1: goesup -1: goesdown
	virtual double	_osv_extream() = 0;
	virtual int		_extream_bar() = 0;
	virtual DC_EXTREAM _extream_type() = 0;	// 1: upper extream -1: lower extream
	virtual uint64_t _extream_tv() = 0;
	virtual double	_extream_value() = 0;
	// directional change event
	virtual double	_dc_delta_up() = 0;
	virtual double	_dc_delta_down() = 0;
	virtual int		_dc_event_bar() = 0;
	virtual uint64_t _dc_event_tv() = 0;
	virtual double	_dc_event_value() = 0;
	virtual double	_extream_to_dc_event_speed() = 0;
	// overshoot extream
	virtual int		_overshoot_extream_bar() = 0;
	virtual uint64_t _overshoot_extream_tv() = 0;
	virtual double	_overshoot_extream_value() = 0; // latest value or next extream value
	virtual double	_overshoot_over_delta_ratio() = 0;
	virtual double	_dc_event_to_overshoot_extream_speed() = 0;
	virtual double	_extream_to_overshoot_extream_speed() = 0;
};


/**
*	Robust Random Cut Forest interface
*/
class RRCF {
public:
	virtual double getCollusiveDisplacement(int bar) = 0;
	virtual double addPoint(int bar) = 0;
	virtual std::shared_ptr<double[]> getCollusiveDisplacement(void) = 0;
};

/**
*	optimization parameters
*/
struct Parameter {
	std:: string  name;
	int type;
	union {
		int    i;
		uint64_t ulli;
		bool   b;
		float  f;
		double d;
		char   s[8];
		void*  v;
	} u;
	Parameter() {
		name = "";
		u.d = 0;
		type = 0;
	}
	Parameter(char* name_, char* type_name_, int v) { type = 0; name = name_; u.i = v; }
	Parameter(char* name_, char* type_name_, uint64_t v) { type = 0; name = name_; u.ulli = v; }
	Parameter(char* name_, char* type_name_, bool v) { type = 0; name = name_; u.b = v; }
	Parameter(char* name_, char* type_name_, float v) { type = 0; name = name_; u.f = v; }
	Parameter(char* name_, char* type_name_, double v) { type = 0; name = name_; u.d = v; }
	Parameter(char* name_, char* type_name_, char* v) { type = 0; name = name_; std::strncpy(u.s, (char*)v, 8); }
	Parameter(char* name_, char* type_name_, void* v) { type = 0; name = name_; u.v = v; }

	// Functionality
	std::string &_name() {return name;}
	int     _type()  { return type; }
	int		_int() { return u.i; }
	uint64_t _uint64_t() { return u.ulli; }
	bool	_bool() { return u.b; }
	float	_float() { return u.f; }
	double	_double() { return u.d; }
	char *	_chars() { return u.s; }

	// Setter
	void setInt(char* name_, char* type_name_, int v) { type = 0; name = name_; u.i = v; }
	void setUint64_t(char* name_, char* type_name_, uint64_t v) { type = 0; name = name_; u.ulli = v; }
	void setBool(char* name_, char* type_name_, bool v) { type = 0; name = name_; u.b = v; }
	void setFloat(char* name_, char* type_name_, float v) { type = 0; name = name_; u.f = v; }
	void setDouble(char* name_, char* type_name_, double v) { type = 0; name = name_; u.d = v; }
	void setChars(char* name_, char* type_name_, char *v) { type = 0; name = name_; std::strncpy(u.s, (char*)v, 8); }
	void setVoid(char* name_, char* type_name_, void* v) { type = 0; name = name_; u.v = v; }

	// Getter
	int		getInt() { assert(type == 0); return u.i;}
	uint64_t getUint64_t() { assert(type == 1); return u.ulli; }
	bool	getBool()  { assert(type == 2); return u.b; }
	bool	getFloat() { assert(type == 3); return u.f; }
	bool	getDouble() { assert(type == 4); return u.d; }
	char   *getChars() { assert(type == 5); return u.s; }
	void   *getVoid() { assert(type == 6); return u.v; }


	void* _value(char* type_name) {
		int type_id = _type_id(type_name);
		assert(type_id == type);
		switch (type_id) {
		case 0:return (void*)&u.i;
		case 1:return (void*)&u.ulli;
		case 2:return (void*)&u.b;
		case 3:return (void*)&u.f;
		case 4:return (void*)&u.d;
		case 5:return (void*)&u.s;
		case 6:return (void*)&u.v;
		default:assert(0);
		}
	}

private:

	int _type_id(char* type_name) {
		if (std::strcmp(type_name, "int") == 0)return 0;
		if (std::strcmp(type_name, "unsigned long long int") == 0 || std::strcmp(type_name, "uint64_t") == 0)return 1;
		if (std::strcmp(type_name, "bool") == 0)return 2;
		if (std::strcmp(type_name, "float") == 0)return 3;
		if (std::strcmp(type_name, "double") == 0)return 4;
		if (std::strcmp(type_name, "chars") == 0)return 5;
		if (std::strcmp(type_name, "void *") == 0)return 6;
		assert(0);
	}

	void* _value(int type_id) {
		switch (type_id) {
		case 0:return (void*)&u.i;
		case 1:return (void*)&u.ulli;
		case 2:return (void*)&u.b;
		case 3:return (void*)&u.f;
		case 4:return (void*)&u.d;
		case 5:return (void*)&u.s;
		case 6:return (void*)&u.v;
		default:assert(0);
		}
	}

	void setValue(char* name_, char* type_name_, void* v) {
		name = name_;
		int type = _type_id(type_name_);
		switch (type) {
		case 0: {u.i = *(int*)v; break; }
		case 1: {u.ulli = *(uint64_t*)v; break; }
		case 2: {u.b = *(bool*)v; break; }
		case 3: {u.f = *(float*)v; break; }
		case 4: {u.d = *(double*)v; break; }
		case 5: {std::strncpy(u.s, (char*)v, 8); break; }
		case 6: {u.v = v; break; }
		default:assert(0);
		}
	}

};

/**
*	External functions
*/
class UserRuleBase;

/**
 * Initial setup
 *
 * @input_dir_ input data directory
 * @output_dir_ output data directory
 * @random_seed seed > 0 of random generator  or get from the random_device if negative
 * @user_rule_realtime_ user-rule for real-time processing 
 * @return true if success.
 */
extern bool commonSetup(std::string& input_dir_, std::string &output_dir_, UserRuleBase* user_rule_realtime_, int64_t random_seed = -1);
extern bool endCommonTerminate();

// user defined memory access
extern std::shared_ptr<FloatArrayDataIF> newFloatArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len=0, bool _reverse_access = true);
extern std::shared_ptr<DoubleArrayDataIF> newDoubleArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len=0, bool _reverse_access = true);
extern std::shared_ptr<IntArrayDataIF> newIntArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len=0, bool _reverse_access = true);
extern std::shared_ptr<EdgeDataIoTArrayDataIF> newEdgeDataIoTArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true);
extern std::shared_ptr<EdgeDataDoubleIoTArrayDataIF> newEdgeDataDoubleIoTArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true);
extern std::shared_ptr<TOHLCVIoTArrayDataIF> newTOHLCVIoTArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int de_count_, int sz_len, bool _reverse_access = true);
extern std::shared_ptr<TOHLCVArrayDataIF> newTOHLCVArrayData(TfInfoIF* _tfinfotf, DATA_ELEM_TYPE de_type, int sz_len, bool _reverse_access = true);

// platform defined timeseries accessor, TfInfoIF::initTimeSeries must defined the timeseries.  
extern std::shared_ptr<TickAccessorIF> newTickAccessor(TfInfoIF* _tfinfotf, bool _reverse_access= true);
std::shared_ptr<TOHLCVAccessorIF> newTohlcvAccessor(TfInfoIF* _tfinfotf, bool _reverse_access = true);
std::shared_ptr<TimeAccessorIF> newTimeAccessor(TfInfoIF* _tfinfotf, bool _reverse_access = true);
std::shared_ptr<EdgeDataIoTAccessorIF> newEdgeDataIoTAccessor(TfInfoIF* _tfinfotf, bool _reverse_access = true);
std::shared_ptr<EdgeDataDoubleIoTAccessorIF> newEdgeDataDoubleIoTAccessor(TfInfoIF* _tfinfotf, bool _reverse_access = true);

extern const char* exchange_code_to_name[(int)NUM_NAMED_EXCHANGE];
extern const char* instrument_code_to_name[(int)NUM_NAMED_INSTRUMENT];
extern const char* timeframe_code_to_name[];

extern uint64_t  timeframe_interval_in_us[];
extern std::map<std::string, int> instrument_name_to_code;
extern std::map<std::string, int> exchange_name_to_code;
extern std::map<std::string, int> timeframe_name_to_code;

extern int instrument_digit[NUM_EXCHANGE][NUM_INSTRUMENT];
extern int getDigit(int exchange, int instrument);
extern double getRoundDigit(int exchange, int instrument);


/**
*	miscellaneous utils
*/
///  for quick search of min/max point in the lookback-period  
struct  ValandIdx {
	double  val;
	int     idx;
	ValandIdx(double _val, int _idx) :val(_val), idx(_idx) {}
};

extern std::string input_dir;
extern std::string output_dir;

extern std::string string_format(const std::string fmt_str, ...);

extern std::string timeNow_local_To_utc_YYYY_mm_dd_HH_MM_SS_mmmmmm(const char* fmt = "%Y-%m-%dT%H:%M:%S");

extern std::string timeSinceEpoch_YYYY_mm_dd_HH_MM_SS_mmmmmm(uint64_t  usec_since_epoch, const char* fmt = "%Y-%m-%dT%H:%M:%S");

extern std::string timeSinceEpoch_YYYY_mm_dd_HH_MM_SS(uint64_t  usec_since_epoch, const char* fmt = "%Y-%m-%dT%H:%M:%S");

//extern std::string timeSinceEpoch_utc_To_local_YYYY_mm_dd_HH_MM_SS_mmmmmm( uint64_t  usec_since_epoch );

extern uint64_t timeStringToTimeval(const char* tstr);

extern const  char* wday[7];
extern void  localtimeLocked(uint64_t time_us, std::tm& _tm);

extern void  gmtimeLocked(uint64_t time_us, std::tm& _tm);

extern std::istream& safeGetline(std::istream& is, std::string& t, const char delim);

extern std::vector<std::string> split_delim(const std::string& s, char delim);


/**
*	indicators
*/
extern bool directionalChange(TfInfoIF* tf_i,
	double delta_up, double delta_down,
	std::vector< std::shared_ptr<DirectionalChangeInfoIF> >& dc_info,
	std::shared_ptr<DoubleArrayDataIF> dc_dc = nullptr, std::shared_ptr <DoubleArrayDataIF> dc_ov = nullptr);

extern void calculateReturns(std::shared_ptr<DoubleArrayDataIF> return_ratio);

extern void caluculateAtrAdx(std::shared_ptr<DoubleArrayDataIF> atr[], 
	std::shared_ptr<DoubleArrayDataIF> atr_velocity[], std::shared_ptr<DoubleArrayDataIF> atr_accel[],
	std::shared_ptr<DoubleArrayDataIF> adx[], std::shared_ptr<DoubleArrayDataIF> plus_dm[], 
	std::shared_ptr<DoubleArrayDataIF> minus_dm[], std::shared_ptr<DoubleArrayDataIF> adx_velocity[], 
	std::shared_ptr<DoubleArrayDataIF> adx_accel[], int num_period, int period_arr[]);

extern void caluculateAtr(std::shared_ptr<DoubleArrayDataIF> atr[], std::shared_ptr<DoubleArrayDataIF> atr_velocity[], 
	std::shared_ptr<DoubleArrayDataIF> atr_accel[], int num_period, int period_arr[]);

extern void calculateReturnMeanStdddev(std::shared_ptr<DoubleArrayDataIF> series, int num_period, int period[],
	std::shared_ptr<DoubleArrayDataIF> mean_arr[], std::shared_ptr<DoubleArrayDataIF> stddev_arr[]);

extern void calculateShortLongRatio(int num_numerators, std::shared_ptr<DoubleArrayDataIF> numerator[],
	std::shared_ptr<DoubleArrayDataIF> result[], std::shared_ptr<DoubleArrayDataIF> denominator);

extern void calculateReturnMin(std::shared_ptr<DoubleArrayDataIF> series, int period, std::deque< ValandIdx >& min_window, std::shared_ptr<DoubleArrayDataIF> series_min);

extern void calculateReturnMax(std::shared_ptr<DoubleArrayDataIF> series, int period, std::deque< ValandIdx >& max_window, std::shared_ptr<DoubleArrayDataIF> series_max);

extern void calculatePriceMin(int period, std::deque< ValandIdx >& min_window, std::shared_ptr<DoubleArrayDataIF> series_min);

extern void calculatePriceMax(int period, std::deque< ValandIdx >& max_window, std::shared_ptr<DoubleArrayDataIF> series_max);

extern void calculatePriceMeanStdddev(int num_period, int period[], std::shared_ptr<DoubleArrayDataIF> mean_arr[], std::shared_ptr<DoubleArrayDataIF> stddev_arr[]);

extern void calculatePriceStdddevOverPrice(int num_period, int period[], std::shared_ptr<DoubleArrayDataIF> stddev_arr[], std::shared_ptr<DoubleArrayDataIF> stddev_over_price_arr[]);

extern double getValueFromPercentile(std::vector<double>& sorted_data, const double f); // Get value at percentile(0 - 1.0) from a sorted vector

extern double getValueFromPercentile(size_t num, double* sorted_data, const double f);

extern double getPercentileOfValueByTable(double val, std::vector<double>& percentile_tbl); // return percentile which is from 0 to 1.0 including.

/// Robust Random Cut Forest
extern std::shared_ptr<RRCF> createRRCF(int num_trees_, int tree_size_, std::function<EdgeDataDouble_IoT* (int)> func_, int iot_de_count_, std::vector<int>& bars_, int num_threads_, int64_t seed = -1);

/// data pump
extern void pumpEdgeDataIoT(int ex, int in, int tf, EdgeData_IoT* data);
extern void pumpEdgeDataIoT(int ex, int in, int tf, EdgeDataDouble_IoT* data);
#if 0
extern void pumpEdgeDataIoTandCompress(int ex, int in, int tf, EdgeData_IoT* data);
extern void pumpEdgeDataIoTandCompress(int ex, int in, int tf, EdgeDataDouble_IoT* data);
extern void pumpTOHLCVIoT(int ex, int in, int tf, TOHLCV_IoT* data);
extern void pumpTOHLCVIoTandCompress(int ex, int in, int tf, TOHLCV_IoT* data);
extern void pumpTickData(int ex, int in, int tf, TickData* data);
extern void pumpTickDataandCompress(int ex, int in, int tf, TickData* data);
extern void pumpTOHLCV(int ex, int in, int tf, TOHLCV* data);
extern void pumpTOHLCVandCompress(int ex, int in, int tf, TOHLCV* data);
/// batch data pump
extern void pumpEdgeDataIoTBatch(int ex, int in, int tf, EdgeData_IoT* data, int count, bool reset_series);
extern void pumpEdgeDataIoTBatch(int ex, int in, int tf, EdgeDataDouble_IoT* data, int count, bool reset_series);
extern void pumpEdgeDataIoTandCompressBatch(int ex, int in, int tf, EdgeData_IoT* data, int count, bool reset_series);
extern void pumpEdgeDataIoTandCompressBatch(int ex, int in, int tf, EdgeDataDouble_IoT* data, int count, bool reset_series);
extern void pumpTOHLCVIoTBatch(int ex, int in, int tf, TOHLCV_IoT* data, int count, bool reset_series);
extern void pumpTOHLCVIoTandCompressBatch(int ex, int in, int tf, TOHLCV_IoT* data, int count, bool reset_series);
extern void pumpTickDataBatch(int ex, int in, int tf, TickData* data, int count, bool reset_series);
extern void pumpTickDataAndCompressBatch(int ex, int in, int tf, TickData* data, int count, bool reset_series);
extern void pumpTOHLCVBatch(int ex, int in, int tf, TOHLCV* data, int count, bool reset_series);
extern void pumpTOHLCVandCompressBatch(int ex, int in, int tf, TOHLCV* data, int count, bool reset_series);
#endif


/// application
extern int simulator_main(
	std::string& period,
	UserRuleBase* user_rule_,
	std::string& data_input_dir_
);

}

/**
*  logging
*  Plog - portable and simple log for C++
*  Documentation and sources: https://github.com/SergiusTheBest/plog
*/
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>


