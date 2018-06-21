<?php

/**
 * @file
 * Provide Drush command to redo update schema commands.
 * */

/**
 * Implements hook_drush_command().
 */
function lime_redo_updates_drush_command() {
  $items['lime-get-schema-version'] = array(
    'description' => 'Returns the schema version of a module.',
    'arguments' => array(
      'module_name' => 'The module you want the schema version from.',
    ),
    'required-arguments' => TRUE,
    'category' => 'LimeDevTools',
    'examples' => array(
      'drush lime-get-schema-version paragraphs' => 'Shows current schema version.',
    ),
    'aliases' => array('lgsv'),
  );

  $items['lime-set-schema-version'] = array(
    'description' => 'Set the schema version of a module.',
    'arguments' => array(
      'module_name' => 'The module you want to set the schema version on.',
      'schema_version' => 'The schema version.',
    ),
    'required-arguments' => TRUE,
    'category' => 'LimeDevTools',
    'examples' => array(
      'drush lime-set-schema-version paragraphs 8001' => 'Shows current schema version, and overwrite it wit given version.',
    ),
    'aliases' => array('lssv'),
  );

  $items['lime-update-redo-update-from'] = array(
    'description' => 'Redo last schema updates of module.',
    'arguments' => array(
      'module_name' => 'The module that you want to update',
      'schema_version' => 'The schema version to run updates from so 8001 wil run updates 8001 and up.',
    ),
    'category' => 'LimeDevTools',
    'examples' => array(
      'drush lime-redo-last-update paragraphs' => 'Reruns updates from a given schema version for $module.',
    ),
    'aliases' => array('luuf'),
  );

  $items['lime-update-redo-last-update'] = array(
    'description' => 'Redo last schema update of module.',
    'arguments' => array(
      'module_name' => 'The module that you want to update',
    ),
    'category' => 'LimeDevTools',
    'examples' => array(
      'drush lime-redo-last-update paragraphs' => 'Checks current schema version, downgrades it by 1, updates database and runs updb on module.',
    ),
    'aliases' => array('lulu'),
  );

  return $items;
}

/**
 * Get the schema version of the given module.
 *
 * @param string $module_name
 *   The module name.
 */
function drush_lime_redo_updates_lime_get_schema_version($module_name) {

  $schema_version = drupal_get_installed_schema_version($module_name);

  echo PHP_EOL;
  echo "The module " . $module_name . " has version: " . $schema_version . PHP_EOL;
  echo PHP_EOL;
}

/**
 * Set the schema version for the given module.
 *
 * @param string $module_name
 *   The module name.
 * @param int $schema_version
 *   The schema version.
 */
function drush_lime_redo_updates_lime_set_schema_version($module_name, $schema_version) {

  $old_schema_version = drupal_get_installed_schema_version($module_name);
  drupal_set_installed_schema_version($module_name, $schema_version);

  echo PHP_EOL;
  echo "The module " . $module_name . " had version: " . $old_schema_version . PHP_EOL;
  echo PHP_EOL;
  echo "The module " . $module_name . " now has version: " . $schema_version . PHP_EOL;
  echo PHP_EOL;
}

/**
 * Redo updates from a specific version for module name.
 *
 * @param string $module_name
 *   The module name.
 * @param int $schema_version
 *   The schema version.
 */
function drush_lime_redo_updates_lime_update_redo_update_from($module_name, $schema_version) {
  drush_lime_redo_updates_lime_set_schema_version($module_name, $schema_version);

  drush_invoke('updatedb', [$module_name], '--no-backup');
}

/**
 * Redo last schema update for module name.
 *
 * @param string $module_name
 *   The module name.
 */
function drush_lime_redo_updates_lime_update_redo_last_update($module_name) {

  $old_schema_version = drupal_get_installed_schema_version($module_name);
  // Set schema version 1 back.
  $schema_version = $old_schema_version - 1;
  drush_lime_redo_updates_lime_update_redo_update_from($module_name, $schema_version);

}
