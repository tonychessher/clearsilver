// Generated file. Do not edit.

#define NUM_STATES 24

enum state_internal_enum {
    STATE_I_TEXT,
    STATE_I_TAG_START,
    STATE_I_TAG_NAME,
    STATE_I_TAG_SPACE,
    STATE_I_TAG_CLOSE,
    STATE_I_ATTR,
    STATE_I_ATTR_SPACE,
    STATE_I_VALUE,
    STATE_I_VALUE_TEXT,
    STATE_I_VALUE_Q,
    STATE_I_VALUE_DQ,
    STATE_I_COMMENT,
    STATE_I_COMMENT_OPEN,
    STATE_I_COMMENT_IN,
    STATE_I_COMMENT_CLOSE,
    STATE_I_JS_TEXT,
    STATE_I_JS_COMMENT,
    STATE_I_JS_COMMENT_OPEN,
    STATE_I_JS_COMMENT_IN,
    STATE_I_JS_COMMENT_CLOSE,
    STATE_I_JS_LT,
    STATE_I_JS_FILE,
    STATE_I_CSS_FILE,
    STATE_I_NULL,
};

static state states_external[] = {
    HTML_STATE_TEXT,
    HTML_STATE_TAG,
    HTML_STATE_TAG,
    HTML_STATE_TAG,
    HTML_STATE_TEXT,
    HTML_STATE_ATTR,
    HTML_STATE_ATTR,
    HTML_STATE_VALUE,
    HTML_STATE_VALUE,
    HTML_STATE_VALUE,
    HTML_STATE_VALUE,
    HTML_STATE_COMMENT,
    HTML_STATE_COMMENT,
    HTML_STATE_COMMENT,
    HTML_STATE_COMMENT,
    HTML_STATE_TEXT,
    HTML_STATE_TEXT,
    HTML_STATE_TEXT,
    HTML_STATE_TEXT,
    HTML_STATE_TEXT,
    HTML_STATE_TEXT,
    HTML_STATE_JS_FILE,
    HTML_STATE_CSS_FILE,
    HTML_STATE_TEXT,
};

static const char *states_external_name[] = {
    "text",
    "tag",
    "attr",
    "value",
    "comment",
    "js_file",
    "css_file",
};

static struct statetable_transitions_s state_transitions[] = {
    { ":default:", STATE_I_NULL, STATE_I_NULL },
    { ":default:", STATE_I_CSS_FILE, STATE_I_CSS_FILE },
    { ":default:", STATE_I_JS_FILE, STATE_I_JS_FILE },
    { ":default:", STATE_I_JS_LT, STATE_I_JS_TEXT },
    { "!", STATE_I_JS_LT, STATE_I_JS_COMMENT },
    { "/", STATE_I_JS_LT, STATE_I_TAG_NAME },
    { ":default:", STATE_I_JS_TEXT, STATE_I_JS_TEXT },
    { "<", STATE_I_JS_TEXT, STATE_I_JS_LT },
    { ":default:", STATE_I_JS_COMMENT_CLOSE, STATE_I_JS_COMMENT_IN },
    { "-", STATE_I_JS_COMMENT_CLOSE, STATE_I_JS_COMMENT },
    { ":default:", STATE_I_JS_COMMENT_IN, STATE_I_JS_COMMENT_IN },
    { "-", STATE_I_JS_COMMENT_IN, STATE_I_JS_COMMENT_CLOSE },
    { ":default:", STATE_I_JS_COMMENT_OPEN, STATE_I_JS_COMMENT },
    { ">", STATE_I_JS_COMMENT_OPEN, STATE_I_JS_TEXT },
    { "-", STATE_I_JS_COMMENT_OPEN, STATE_I_JS_COMMENT_IN },
    { ":default:", STATE_I_JS_COMMENT, STATE_I_JS_COMMENT },
    { ">", STATE_I_JS_COMMENT, STATE_I_JS_TEXT },
    { "-", STATE_I_JS_COMMENT, STATE_I_JS_COMMENT_OPEN },
    { ":default:", STATE_I_VALUE_DQ, STATE_I_VALUE_DQ },
    { "\"", STATE_I_VALUE_DQ, STATE_I_TAG_SPACE },
    { ":default:", STATE_I_VALUE_Q, STATE_I_VALUE_Q },
    { "'", STATE_I_VALUE_Q, STATE_I_TAG_SPACE },
    { ":default:", STATE_I_VALUE_TEXT, STATE_I_VALUE_TEXT },
    { " \t\n\r?", STATE_I_VALUE_TEXT, STATE_I_TAG_SPACE },
    { ">", STATE_I_VALUE_TEXT, STATE_I_TAG_CLOSE },
    { ":default:", STATE_I_VALUE, STATE_I_VALUE_TEXT },
    { ">", STATE_I_VALUE, STATE_I_TAG_CLOSE },
    { " \t\n\r?", STATE_I_VALUE, STATE_I_VALUE },
    { "\"", STATE_I_VALUE, STATE_I_VALUE_DQ },
    { "'", STATE_I_VALUE, STATE_I_VALUE_Q },
    { "=", STATE_I_ATTR_SPACE, STATE_I_VALUE },
    { "/", STATE_I_ATTR_SPACE, STATE_I_TAG_SPACE },
    { "A-Za-z0-9_:-", STATE_I_ATTR_SPACE, STATE_I_ATTR },
    { " \t\n\r?", STATE_I_ATTR_SPACE, STATE_I_ATTR_SPACE },
    { ">", STATE_I_ATTR_SPACE, STATE_I_TAG_CLOSE },
    { " \t\n\r?", STATE_I_ATTR, STATE_I_ATTR_SPACE },
    { "=", STATE_I_ATTR, STATE_I_VALUE },
    { "/", STATE_I_ATTR, STATE_I_TAG_SPACE },
    { ">", STATE_I_ATTR, STATE_I_TAG_CLOSE },
    { "A-Za-z0-9_:-", STATE_I_ATTR, STATE_I_ATTR },
    { ":default:", STATE_I_TAG_CLOSE, STATE_I_TEXT },
    { "<", STATE_I_TAG_CLOSE, STATE_I_TAG_START },
    { "/", STATE_I_TAG_SPACE, STATE_I_TAG_SPACE },
    { "A-Za-z0-9_:-", STATE_I_TAG_SPACE, STATE_I_ATTR },
    { " \t\n\r?", STATE_I_TAG_SPACE, STATE_I_TAG_SPACE },
    { ">", STATE_I_TAG_SPACE, STATE_I_TAG_CLOSE },
    { ":default:", STATE_I_COMMENT_CLOSE, STATE_I_COMMENT_IN },
    { "-", STATE_I_COMMENT_CLOSE, STATE_I_COMMENT },
    { ":default:", STATE_I_COMMENT_IN, STATE_I_COMMENT_IN },
    { "-", STATE_I_COMMENT_IN, STATE_I_COMMENT_CLOSE },
    { ":default:", STATE_I_COMMENT_OPEN, STATE_I_COMMENT },
    { ">", STATE_I_COMMENT_OPEN, STATE_I_TEXT },
    { "-", STATE_I_COMMENT_OPEN, STATE_I_COMMENT_IN },
    { ":default:", STATE_I_COMMENT, STATE_I_COMMENT },
    { ">", STATE_I_COMMENT, STATE_I_TEXT },
    { "-", STATE_I_COMMENT, STATE_I_COMMENT_OPEN },
    { ">", STATE_I_TAG_NAME, STATE_I_TAG_CLOSE },
    { " \t\n\r?", STATE_I_TAG_NAME, STATE_I_TAG_SPACE },
    { "A-Za-z0-9/_?:-", STATE_I_TAG_NAME, STATE_I_TAG_NAME },
    { "!", STATE_I_TAG_START, STATE_I_COMMENT },
    { "A-Za-z0-9/_?:-", STATE_I_TAG_START, STATE_I_TAG_NAME },
    { ":default:", STATE_I_TEXT, STATE_I_TEXT },
    { "<", STATE_I_TEXT, STATE_I_TAG_START },
    { NULL, STATEMACHINE_ERROR, STATEMACHINE_ERROR }
};
