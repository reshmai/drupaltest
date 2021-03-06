<?php
/**
 * @file
 * Contains admin forms and code.
 */

/**
 * Form definition for menu fields configuration.
 */
function menu_fields_field_configuration_form() {

  $form['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled Menu Fields'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $header = array(
    'menu_name' => t('Menu name'),
    'operation_field' => t('Fields'),
    'operation_display' => t('Display'),
  );

  $options = array();
  $default_values = array();

  $menus = menu_get_menus();
  $selected_menus = menu_fields_enabled_menus();

  foreach ($menus as $key => $value) {

    $options[$key] = array('menu_name' => $value);

    // Add manage fields/display link when menu is selected
    if (in_array($key, $selected_menus)) {
      $default_values[$key] = TRUE;

      $options[$key]['operation_field'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => t('Manage fields'),
          '#href' => 'admin/structure/menu_fields/' . menu_fields_create_machine_name($key) . '/fields',
        ),
      );
      $options[$key]['operation_display'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => t('Manage display'),
          '#href' => 'admin/structure/menu_fields/' . menu_fields_create_machine_name($key) . '/display',
        ),
      );

    }
    else {
      $default_values[$key] = FALSE;
      $options[$key]['operation_field'] = '';
      $options[$key]['operation_display'] = '';
    }
  }

  $form['fields']['menus'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No menus available.'),
    '#multiple' => TRUE,
    '#default_value' => $default_values,
    '#js_select' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for the menu fields administration form.
 *
 * @see menu_fields_field_configuration_form().
 */
function menu_fields_field_configuration_form_submit($form, &$form_state) {
  $menus = array();

  foreach ($form_state['values']['menus'] as $key => $value) {
    if ($key === $value) {
      $menus[] = $value;
    }
  }

  menu_fields_save_enabled_menus($menus);
  drupal_set_message(t('Field settings saved.'));
}
