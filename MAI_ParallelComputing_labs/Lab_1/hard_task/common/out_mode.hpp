#ifndef __COMMON_OUTMODE_HPP__
#define __COMMON_OUTMODE_HPP__

/**
 * @brief Output mode of results
 * @example OutMode::FromattedOutput - Allows the implementation to use the formatted output in a readable form
 * @example OutMode::TableOutput     - Allows the implementation to use the output in tabular form. For example: 10;20;30;40
 * @example OutMode::Mute            - Prohibits output to cout
 */
enum class OutMode {
    FormattedOutput,
    TableOutput,
    Mute
};

#endif // __COMMON_OUTMODE_HPP__