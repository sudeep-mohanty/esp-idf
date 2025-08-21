# Register all of the "performance" tests as a component

# In order for the cases defined by `TEST_CASE` in "performance" to be linked into
# the final elf, the component can be registered as WHOLE_ARCHIVE
idf_component_register(SRC_DIRS "." "crit_speed" "queue_contention" "queue_speed" "lock_contention_end_to_end"
                       INCLUDE_DIRS "include" "../include"
                       PRIV_REQUIRES unity test_utils
                       WHOLE_ARCHIVE)

# Enable custom test framework mapping for this component's tests
target_compile_definitions(${COMPONENT_LIB} PRIVATE configTARGET_TEST_USE_CUSTOM_SETTING=1)
