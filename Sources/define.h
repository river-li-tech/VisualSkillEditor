#pragma once
#include <QObject>
#include <QString>

static const bool ENABLE_STARTUP_LOAD_FILE = true;//load file startup
static const bool ENABLE_AUTO_SAVE = true;//auto save all files
static const double INTERVAL_AUTO_SAVE = 30000;//auto save interval time(ms)

//SkillInst
static const int SKILLINST_LOGIC_PARAM_COUNT = 20;//number of logic params in SkillInst.txt
static const QString SKILLINST_FILE_NAME = "SkillInst.txt";//SkillInst.txt file path
static const QString SKILLINST_WORK_DIR_DEFAULT = "/WorkSpace/";//search path for SkillInst.txt

//SkillGfx
static const int SKILLGFX_LOGIC_PARAM_COUNT = 30;//number of logic params in SkillGfx.txt
static const QString SKILLGFX_FILE_NAME = "SkillGfx.txt";//SkillGfx.txt file path
static const QString SKILLGFX_WORK_DIR_DEFAULT = "/WorkSpace/"; //search path for SkillGfx.txt

//SkillScript
static const QString SKILLSCRIPT_SKILL_ID_DEFAULT = "root";//default skill root
static const QString SKILLSCRIPT_ADD_SKILL_NODE_ID = "wait";//default node id for "add node"
static const QString SKILLSCRIPT_ADD_SKILL_NODE_OPSTATE_ID = "opstate";//default node id for "add node"
static const QString SKILLSCRIPT_ADD_SKILL_NODE_TEST_ID = "test";//default node id for "add node"
static const QString SKILLSCRIPT_ADD_SKILL_NODE_JUMP_ID = "jump";//default node id for "add node"
static const QString SKILLSCRIPT_ADD_SKILL_NODE_END_ID = "end";//default node id for "add node"
static const QString SKILLSCRIPT_ADD_SKILL_SECTION_ID = "onstart";//default section node id for skill script
static const QString SKILLSCRIPT_WORK_DIR_DEFAULT = "/WorkSpace/";//search path for skill script file(1st)

static const int SKILLNODE_REMARK_MAX_COUNT = 120;//max count for remark text
static const QString SKILLPARAM_ENUM_LOGICPARAM_NAME = "enum.logicparam";//name for enum.logparam
static const QString SKILLPARAM_ENUM_NODETYPE_NAME = "enum.nodetype";//name for enum.nodetype
static const int SKILLPARAM_REF_COMBO_FIXED_WIDTH = 90;//fixed with for reference combo
static const int SKILLPARAM_REVERT_BUTTON_FIXED_WIDTH = 20;//fixed with for revert button
static const QString SKILLPARAM_REVERT_BUTTON_TEXT = "<-";//text for revert button

static const QString SKILLNODE_DEFAULT_BACKGROUND_COLOR = "#FFFFFF";
static const QString SKILLNODE_TOOL_BACKGROUND_COLOR = "#9fdf9f";
static const QString SKILLNODE_SELECTED_BACKGROUND_COLOR = "#D0E0FF";

//SkillSpec
static const QString SKILLSPEC_FILE_PATH = "Config/SkillSpec.xml";//SkillSpec.xml file name
static const int SKILLSPEC_TOOL_NODE_TYPE = 8;

static const double STATUS_BAR_MESSAGE_WAIT_TIME = 3000;//auto save interval time(ms)

static const QString SKILLSCRIPT_REFINFOS_TAG_NAME = "infos";
static const QString SKILLSCRIPT_REFINFO_TAG_NAME = "info";



///////////////////////////////////////////////////////////////////////////
//signal reason for modify skill data
enum class SkillNotifyReason
{
    //SkilInst
    R_SKILLINST_LOAD,
    R_SKILLINST_SAVE,
    R_SKILLINST_CLEAR,
    R_SKILLINST_ADD_DATA,
    R_SKILLINST_REMOVE_DATA,

    //SkillInstData
    R_SKILLINSTDATA_ID,
    R_SKILLINSTDATA_DESC,
    R_SKILLINSTDATA_LOGIC,
    R_SKILLINSTDATA_ISCLIENTSKILL,
    R_SKILLINSTDATA_PARAMS,
    R_SKILLINSTDATA_SELECTION,

    //SkillGfx
    R_SKILLGFX_LOAD,
    R_SKILLGFX_SAVE,
    R_SKILLGFX_CLEAR,
    R_SKILLGFX_ADD_DATA,
    R_SKILLGFX_REMOVE_DATA,

    //SkillScript
    R_SKILLSCRIPT_LOAD,
    R_SKILLSCRIPT_SAVE,
    R_SKILLSCRIPT_CLEAR,

    //SkillScriptNode
    R_SKILLSCRIPTNODE_ID,
    R_SKILLSCRIPTNODE_ADD_NODE,
    R_SKILLSCRIPTNODE_REMOVE_NODE,
    R_SKILLSCRIPTNODE_MOVE_NODE,
    R_SKILLSCRIPTNODE_ADD_PARAM,
    R_SKILLSCRIPTNODE_REMOVE_PARAM,

    //SkillParam
    R_SKILLSCRIPTNODEPARAM_PARAM_NAME,
    R_SKILLSCRIPTNODEPARAM_PARAM_TYPE,
    R_SKILLSCRIPTNODEPARAM_PARAM_NUMBER,
    R_SKILLSCRIPTNODEPARAM_PARAM_STRING,
    R_SKILLSCRIPTNODEPARAM_PARAM_REF,
    R_SKILLSCRIPTNODEPARAM_PARAM_REF_NUMBER,
};

typedef enum _AskSaveResult
{
    R_SAVE,
    R_DISCARD,
    R_CANCEL,
}AskSaveResult;

typedef enum _JumpCondType
{
    TYPE_NONE = -1,
    TYPE_IF_FALSE = 0,
    TYPE_IF_TRUE = 1,
    TYPE_LOOP_FALSE = 2,
    TYPE_LOOP_TRUE = 3,
}JumpCondType;

typedef enum _OpStateType
{
    OP_NONE = 0,
    OP_LOOP = 1,
}OpStateType;
