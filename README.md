# lime_dev_tools

This is a drush script that can be used during drupal module development.

You can use it to do some schema manipulation to test your update hooks.

The following commands are available:

`lime-get-schema-version (lgsv) $module_name`

Returns the current schema version of given module.
 
`lime-get-schema-version (lssv) $module_name $schema_version`

Shows current schema version, and overwrite it wit given version.
 
`lime-update-redo-update-from (luuf) $module_name $schema_version`

Reruns updates from a given schema version for $module.
 
`lime-update-redo-last-update (lulu) $module_name`

Checks current schema version, downgrades it by 1, updates database and runs updb on module.


Where $module_name and $schema_version are the required paramters.

This script was build during the time given by LimoenGroen.
