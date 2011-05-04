<?php
/**
 * Overview form of all components for this webform.
 */
function webform2pdf_admin_settings() {
  $form = array();

  $default = variable_get('webform2pdf_default', '');

  // It is needed because of file upload
  $form['#attributes'] = array('enctype' => 'multipart/form-data');
  $form['base'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['base']['pdf_lib'] = array(
    '#type' => 'textfield',
    '#title' => t('PDF library path'),
    '#default_value' => $default['pdf_lib'],
    '#required' => TRUE,
    '#description' => t('Please enter the path of the TCPDF library. Example: sites/all/libraries/tcpdf'),
  );

  $form['base']['pdf_send_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Attach PDF as an attachment to the e-mails sent to the form recipients.'),
    '#default_value' => $default['pdf_send_email'],
  );

  $form['base']['page_format'] = array(
    '#type' => 'select',
    '#title' => t('Paper size'),
    '#default_value' => $default['page_format'],
    '#options' => array(
      '4A0' => '4A0', '2A0' => '2A0', 'A0' => 'A0',
      'A1' => 'A1', 'A2' => 'A2', 'A3' => 'A3', 'A4' => 'A4',
      'A5' => 'A5', 'A6' => 'A6', 'A7' => 'A7', 'A8' => 'A8',
      'A9' => 'A9', 'A10' => 'A10', 'B0' => 'B0', 'B1' => 'B1',
      'B2' => 'B2', 'B3' => 'B3', 'B4' => 'B4', 'B5' => 'B5',
      'B6' => 'B6', 'B7' => 'B7', 'B8' => 'B8', 'B9' => 'B9',
      'B10' => 'B10', 'C0' => 'C0', 'C1' => 'C1', 'C2' => 'C2',
      'C3' => 'C3', 'C4' => 'C4', 'C5' => 'C5', 'C6' => 'C6',
      'C7' => 'C7', 'C8' => 'C8', 'C9' => 'C9', 'C10' => 'C10',
      'RA0' => 'RA0', 'RA1' => 'RA1', 'RA2' => 'RA2',
      'RA3' => 'RA3', 'RA4' => 'RA4', 'SRA0' => 'SRA0',
      'SRA1' => 'SRA1', 'SRA2' => 'SRA2', 'SRA3' => 'SRA3',
      'SRA4' => 'SRA4', 'LETTER' => t('Letter'), 'LEGAL' => t('Legal'),
      'EXECUTIVE' => t('Executive'), 'FOLIO' => t('Folio'),
    ),
  );

  $form['base']['page_orientation'] = array(
    '#type' => 'radios',
    '#title' => t('Page orientation'),
    '#default_value' => $default['page_orientation'],
    '#options' => array(
      'P' => t('Portrait'),
      'L' => t('Landscape'),
    ),
  );

  $form['img'] = array(
    '#type' => 'fieldset',
    '#title' => t('Images size settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['img']['h_left_logo_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum size of left header logo'),
    '#default_value' => $default['h_left_logo_size'],
    '#size' => 10,
    '#description' => t('Maximum dimensions of the logo on the left side of the header in pixels. Format: width x height. E.g: 270x205'),
  );

  $form['img']['h_right_logo_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum dimensions of right header logo'),
    '#default_value' => $default['h_right_logo_size'],
    '#size' => 10,
    '#description' => t('Maximum dimensions of the logo on the right side of the header in pixels. Format: width x height. E.g: 270x205'),
  );

  $form['img']['f_left_logo_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum dimensions of left footer logo'),
    '#default_value' => $default['f_left_logo_size'],
    '#size' => 10,
    '#description' => t('Maximum dimensions of the logo on the left side of the footer in pixels. <b>WARNING! Setting height greater than 56px could cause error in PDF output.</b> Format: width x height. E.g: 270x205'),
  );

  $form['img']['f_right_logo_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum dimensions of right footer logo'),
    '#default_value' => $default['f_right_logo_size'],
    '#size' => 10,
    '#description' => t('Maximum dimensions of the logo on the right side of the footer in pixels. <b>WARNING! Setting height greater than 56px could cause error in PDF output.</b> Format: width x height. E.g: 270x205'),
  );

  // Header
  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('PDF header'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['header']['h_left_logo'] = array(
    '#type' => 'value',
    '#value' => $default['h_left_logo'],
  );

  if ($default['h_left_logo']) {
    $logo_file = _webform2pdf_get_file($default['h_left_logo']);

    $form['header']['h_left_logo_img'] = array(
      '#type' => 'item',
      '#title' => t('Logo on the left side'),
      '#value' => theme('image', $logo_file->filepath, 'Header left logo.', $logo_file->filename),
    );
    $form['header']['h_left_logo_del'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete left side logo.'),
    );
  }
  else {
    $form['header']['h_left_logo_file'] = array(
      '#type' => 'file',
      '#title' => t('Upload left side logo'),
      '#size' => 60,
      '#maxlength' => 250,
      '#description' => t("Upload left side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $default['h_left_logo_size'])),
    );
  }

  $form['header']['h_txt'] = array(
    '#type' => 'textarea',
    '#title' => t('Header text'),
    '#rows' => '5',
    '#default_value' => $default['h_txt'],
    '#resizable' => FALSE,
    '#description' => t("PDF header text. 5 rows maximum.") . theme('webform_token_help'),
  );

  $form['header']['h_txt_align'] = array(
    '#type' => 'select',
    '#title' => t('Text alignment'),
    '#default_value' => $default['h_txt_align'],
    '#options' => array(
      'L' => t('Align left'),
      'C' => t('Align center'),
      'R' => t('Align right'),
    ),
  );

  $form['header']['h_font_family'] = array(
    '#type' => 'select',
    '#title' => t('Font Family'),
    '#default_value' => $default['h_font_family'],
    '#options' => array(
      'helvetica' => 'Helvetica',
      'times' => 'Times',
      'courier' => 'Courier',
      'dejavusans' => 'Dejavu Sans',
      'dejavuserif' => 'Dejavu Serif',
      'freesans' => 'Free Sans',
      'freeserif' => 'Free Serif',
      'freemono' => 'Free Mono',
    ),
    '#description' => t('Set the font family to be used.'),
  );

  $form['header']['h_font_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Font Size'),
    '#default_value' => $default['h_font_size'],
    '#size' => 2,
    '#maxlength' => 3,
    '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
  );

  $form['header']['h_right_logo'] = array(
    '#type' => 'value',
    '#value' => $default['h_right_logo'],
  );

  if ($default['h_right_logo']) {
    $logo_file = _webform2pdf_get_file($default['h_right_logo']);

    $form['header']['h_right_logo_img'] = array(
      '#type' => 'item',
      '#title' => t('Logo on the right side'),
      '#value' => theme('image', $logo_file->filepath, 'Header right logo.', $logo_file->filename),
    );
    $form['header']['h_right_logo_del'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete right logo.'),
    );
  }
  else {
    $form['header']['h_right_logo_file'] = array(
      '#type' => 'file',
      '#title' => t('Upload right logo'),
      '#size' => 60,
      '#maxlength' => 250,
      '#description' => t("Upload right side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $default['h_right_logo_size'])),
    );
  }

  // PDF body (page)
  $form['page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content of the PDF document'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['page']['p_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Page body'),
    '#rows' => '10',
    '#default_value' => $default['p_body'],
    '#description' => t("The content of the PDF file can be defined here, the text can be formatted with HTML and CSS tags. The form elements can be referred with the following special strings: !vars."
    , array('!vars' => '%pagebreak')) . theme('webform_token_help'),
  );

  $form['page']['format'] = filter_form($default['format']);

  $form['page']['p_txt_align'] = array(
    '#type' => 'select',
    '#title' => t('Text alignment'),
    '#default_value' => $default['p_txt_align'],
    '#options' => array(
      'L' => t('Align left'),
      'C' => t('Align center'),
      'R' => t('Align right'),
      ),
  );

  $form['page']['p_font_family'] = array(
    '#type' => 'select',
    '#title' => t('Font Family'),
    '#default_value' => $default['p_font_family'],
    '#options' => array(
      'helvetica' => 'Helvetica',
      'times' => 'Times',
      'courier' => 'Courier',
      'dejavusans' => 'Dejavu Sans',
      'dejavuserif' => 'Dejavu Serif',
      'freesans' => 'Free Sans',
      'freeserif' => 'Free Serif',
      'freemono' => 'Free Mono',
    ),
    '#description' => t('Set the font family to be used.'),
  );

  $form['page']['p_font_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Font Size'),
    '#default_value' => $default['p_font_size'],
    '#size' => 2,
    '#maxlength' => 3,
    '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
  );

  // Footer
  $form['footer'] = array(
    '#type' => 'fieldset',
    '#title' => t('PDF footer'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['footer']['f_left_logo'] = array(
    '#type' => 'value',
    '#value' => $default['f_left_logo'],
  );

  if ($default['f_left_logo']) {
    $logo_file = _webform2pdf_get_file($default['f_left_logo']);

    $form['footer']['f_left_logo_img'] = array(
      '#type' => 'item',
      '#title' => t('Logo on the left side'),
      '#value' => theme('image', $logo_file->filepath, 'Footer left logo.', $logo_file->filename),
    );
    $form['footer']['f_left_logo_del'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete left side logo.'),
    );
  }
  else {
    $form['footer']['f_left_logo_file'] = array(
      '#type' => 'file',
      '#title' => t('Upload left side logo'),
      '#size' => 60,
      '#maxlength' => 250,
      '#description' => t("Upload left side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $default['f_left_logo_size'])),
    );
  }

  $form['footer']['f_txt'] = array(
    '#type' => 'textarea',
    '#title' => t('Footer text'),
    '#rows' => '2',
    '#default_value' => $default['f_txt'],
    '#resizable' => FALSE,
    '#description' => t("The PDF footer text. 2 rows maximum. The following special element can be used: %pagenumber - number of the page, %totalpage - total page count.") . theme('webform_token_help'),
  );

  $form['footer']['f_txt_align'] = array(
    '#type' => 'select',
    '#title' => t('Text alignment'),
    '#default_value' => $default['f_txt_align'],
    '#options' => array(
      'L' => t('Align left'),
      'C' => t('Align center'),
      'R' => t('Align right'),
    ),
  );

  $form['footer']['f_font_family'] = array(
    '#type' => 'select',
    '#title' => t('Font Family'),
    '#default_value' => $default['f_font_family'],
    '#options' => array(
      'helvetica' => 'Helvetica',
      'times' => 'Times',
      'courier' => 'Courier',
      'dejavusans' => 'Dejavu Sans',
      'dejavuserif' => 'Dejavu Serif',
      'freesans' => 'Free Sans',
      'freeserif' => 'Free Serif',
      'freemono' => 'Free Mono',
    ),
    '#description' => t('Set the font family to be used.'),
  );

  $form['footer']['f_font_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Font Size'),
    '#default_value' => $default['f_font_size'],
    '#size' => 2,
    '#maxlength' => 3,
    '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
  );

  $form['footer']['f_right_logo'] = array(
    '#type' => 'value',
    '#value' => $default['f_right_logo'],
  );

  if ($default['f_right_logo']) {
    $logo_file = _webform2pdf_get_file($default['f_right_logo']);

    $form['footer']['f_right_logo_img'] = array(
      '#type' => 'item',
      '#title' => t('Logo on the right side'),
      '#value' => theme('image', $logo_file->filepath, 'Footer right logo.', $logo_file->filename),
    );
    $form['footer']['f_right_logo_del'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete right logo.'),
    );
  }
  else {
    $form['footer']['f_right_logo_file'] = array(
      '#type' => 'file',
      '#title' => t('Upload right logo'),
      '#size' => 60,
      '#maxlength' => 250,
      '#description' => t("Upload right side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $default['f_right_logo_size'])),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
} // function webform2pdf_admin_settings()

/*
 * webform2pdf_admin_settings_validate: implementation of validate hook
 */
function webform2pdf_admin_settings_validate($form, &$form_state) {
  if ( !is_file($form_state['values']['pdf_lib'] . '/tcpdf.php')   ) {
    form_set_error('pdf_lib', t('Not found TCPDF library: %dir!', array('%dir' => $form_state['values']['pdf_lib'] . '/tcpdf.php') ));
  }

  if ( !preg_match("/^\d+x\d+$/", $form_state['values']['h_left_logo_size'], $t) ) {
    form_set_error('h_left_logo_size', t('Wrong picture size format!'));
  }

  if ( !preg_match("/^\d+x\d+$/", $form_state['values']['h_right_logo_size'], $t) ) {
    form_set_error('h_right_logo_size', t('Wrong picture size format!'));
  }

  if ( !preg_match("/^\d+x\d+$/", $form_state['values']['f_left_logo_size'], $t) ) {
    form_set_error('f_left_logo_size', t('Wrong picture size format!'));
  }

  if ( !preg_match("/^\d+x\d+$/", $form_state['values']['f_right_logo_size'], $t) ) {
    form_set_error('f_right_logo_size', t('Wrong picture size format!'));
  }

  $header = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['h_txt']) ) );

  if ( count($header) > 5) {
    form_set_error('h_txt', t('Up to 5 rows can be set!'));
  }

  $footer = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['f_txt']) ) );
  if ( count($footer) > 2) {
    form_set_error('f_txt', t('Up to 2 rows can be set!'));
  }
} // function webform2pdf_admin_settings_validate()

/*
 * webform2pdf_admin_settings_submit: implementation of submit hook
 */
function webform2pdf_admin_settings_submit($form, &$form_state) {
  // File deleted.
  foreach (array('h_left_logo', 'h_right_logo', 'f_left_logo', 'f_right_logo') as $logo) {
    if ( isset($form_state['values'][$logo . '_del']) ) {
      if ( $form_state['values'][$logo . '_del'] ) {
        if ( (_webform2pdf_use_file($form_state['values'][$logo])-1) == 0) {
          $logo_file = _webform2pdf_get_file($form_state['values'][$logo]);
          file_delete($logo_file->filepath);
        }
        $form_state['values'][$logo] = 0;
      }
    }
  }

  // Header and footer image file save.
  foreach (array('h_left_logo', 'h_right_logo', 'f_left_logo', 'f_right_logo') as $logo) {
    if ( isset($form_state['values'][$logo . '_file']) ) {
      $validators = array(
        'file_validate_is_image' => array(),
        'file_validate_image_resolution' => array($form_state['values'][$logo . '_size']),
      );

      if ( $file = file_save_upload($logo . '_file', $validators, file_directory_path() ) ) {
        file_set_status($file, FILE_STATUS_PERMANENT);
        $form_state['values'][$logo] = $file->fid;
      }
    }
  }

  $save = $form_state['values'];
  foreach (array('h_left_logo_del', 'h_right_logo_del', 'f_left_logo_del', 'f_right_logo_del',
    'h_left_logo_img', 'h_right_logo_img', 'f_left_logo_img', 'f_right_logo_img',
    'h_left_logo_file', 'h_right_logo_file', 'f_left_logo_file', 'f_right_logo_file',
    'op', 'submit', 'form_build_id', 'form_token', 'form_id') as $del) {
    unset($save[$del]);
  }

  variable_set('webform2pdf_default', $save);
} // function webform2pdf_admin_settings_submit()

/**
 * Overview form of all components for this webform.
 */
function webform2pdf_edit_form($form_state, $node) {
  $form = array();

  $result = db_query("SELECT * FROM {webform2pdf} WHERE nid = %d AND enabled = 1", $node->nid);
  $default = db_fetch_array($result);

  $form['enabled'] = array(
    '#default_value' => $default['enabled'],
    '#type' => 'checkbox',
    '#title' => t('Generate PDF Document.'),
  );

  if ($default['enabled']) {
    $webform2pdf_default = variable_get('webform2pdf_default', '');

    // Needed because of file upload
    $form['#attributes'] = array('enctype' => 'multipart/form-data');

    $form['base'] = array(
      '#type' => 'fieldset',
      '#title' => t('General settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['base']['page_format'] = array(
      '#type' => 'select',
      '#title' => t('Paper size'),
      '#default_value' => $default['page_format'],
      '#options' => array(
        '4A0' => '4A0', '2A0' => '2A0', 'A0' => 'A0',
        'A1' => 'A1', 'A2' => 'A2', 'A3' => 'A3', 'A4' => 'A4',
        'A5' => 'A5', 'A6' => 'A6', 'A7' => 'A7', 'A8' => 'A8',
        'A9' => 'A9', 'A10' => 'A10', 'B0' => 'B0', 'B1' => 'B1',
        'B2' => 'B2', 'B3' => 'B3', 'B4' => 'B4', 'B5' => 'B5',
        'B6' => 'B6', 'B7' => 'B7', 'B8' => 'B8', 'B9' => 'B9',
        'B10' => 'B10', 'C0' => 'C0', 'C1' => 'C1', 'C2' => 'C2',
        'C3' => 'C3', 'C4' => 'C4', 'C5' => 'C5', 'C6' => 'C6',
        'C7' => 'C7', 'C8' => 'C8', 'C9' => 'C9', 'C10' => 'C10',
        'RA0' => 'RA0', 'RA1' => 'RA1', 'RA2' => 'RA2',
        'RA3' => 'RA3', 'RA4' => 'RA4', 'SRA0' => 'SRA0',
        'SRA1' => 'SRA1', 'SRA2' => 'SRA2', 'SRA3' => 'SRA3',
        'SRA4' => 'SRA4', 'LETTER' => t('Letter'), 'LEGAL' => t('Legal'),
        'EXECUTIVE' => t('Executive'), 'FOLIO' => t('Folio'),
      ),
    );

    $form['base']['page_orientation'] = array(
      '#type' => 'radios',
      '#title' => t('Page orientation'),
      '#default_value' => $default['page_orientation'],
      '#options' => array(
        'P' => t('Portrait'),
        'L' => t('Landscape'),
      ),
    );

    // E-mail settings
    $form['email'] = array(
      '#type' => 'fieldset',
      '#title' => t('E-mail settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['email']['pdf_send_email'] = array(
      '#type' => 'checkbox',
      '#title' => t('Attach PDF as an attachment to the e-mails sent to the form recipients.'),
      '#default_value' => $default['pdf_send_email'],
    );

    $send_mail = array();
    if ( !empty($node->webform['email']) ) {
      $send_mail['email'] = $node->webform['email'];
    }

    if (is_array($node->webform['emails'])) {
      foreach ($node->webform['emails'] as $eid => $email) {
        $email_addresses = array_filter(explode(',', check_plain($email['email'])));
        foreach ($email_addresses as $key => $email_address) {
          $email_addresses[$key] = webform_format_email_address($email_address, NULL, $node, NULL, FALSE);
        }

        $send_mail[$eid] = implode(', ', $email_addresses);
      }
    }

    if ( count($send_mail) ) {
      $def = unserialize($default['no_send_email_addr']);
      if ( !is_array($def) ) {
        $def = array();
      }

      $form['email']['no_send_email_addr'] = array(
        '#title' => t("Don't attach PDF file"),
        '#type' => 'checkboxes',
        '#options' => $send_mail,
        '#default_value' => $def,
        '#description' => t("PDF file won't be attached to the e-mail sent to the following recipients."),
      );
    }

    // Header
    $form['header'] = array(
      '#type' => 'fieldset',
      '#title' => t('PDF header'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['header']['h_left_logo'] = array(
      '#type' => 'value',
      '#value' => $default['h_left_logo'],
    );

    if ($default['h_left_logo']) {
      $logo_file = _webform2pdf_get_file($default['h_left_logo']);

      $form['header']['h_left_logo_img'] = array(
        '#type' => 'item',
        '#title' => t('Logo on the left side'),
        '#value' => theme('image', $logo_file->filepath, 'Header left logo.', $logo_file->filename),
      );
      $form['header']['h_left_logo_del'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete left side logo.'),
      );
    }
    else {
      $form['header']['h_left_logo_file'] = array(
        '#type' => 'file',
        '#title' => t('Upload left side logo'),
        '#size' => 60,
        '#maxlength' => 250,
        '#description' => t("Upload left side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $webform2pdf_default['h_left_logo_size'])),
      );
    }

    $form['header']['h_txt'] = array(
      '#type' => 'textarea',
      '#title' => t('Header text'),
      '#rows' => '5',
      '#default_value' => $default['h_txt'],
      '#resizable' => FALSE,
      '#description' => t("PDF header text. 5 rows maximum.") . theme('webform_token_help'),
    );

    $form['header']['h_txt_align'] = array(
      '#type' => 'select',
      '#title' => t('Text alignment'),
      '#default_value' => $default['h_txt_align'],
      '#options' => array(
        'L' => t('Align left'),
        'C' => t('Align center'),
        'R' => t('Align right'),
      ),
    );

    $form['header']['h_font_family'] = array(
      '#type' => 'select',
      '#title' => t('Font Family'),
      '#default_value' => $default['h_font_family'],
      '#options' => array(
        'helvetica' => 'Helvetica',
        'times' => 'Times',
        'courier' => 'Courier',
        'dejavusans' => 'Dejavu Sans',
        'dejavuserif' => 'Dejavu Serif',
        'freesans' => 'Free Sans',
        'freeserif' => 'Free Serif',
        'freemono' => 'Free Mono',
      ),
      '#description' => t('Set the font family to be used.'),
    );

    $form['header']['h_font_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Font Size'),
      '#default_value' => $default['h_font_size'],
      '#size' => 2,
      '#maxlength' => 3,
      '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
    );

    $form['header']['h_right_logo'] = array(
      '#type' => 'value',
      '#value' => $default['h_right_logo'],
    );

    if ($default['h_right_logo']) {
      $logo_file = _webform2pdf_get_file($default['h_right_logo']);

      $form['header']['h_right_logo_img'] = array(
        '#type' => 'item',
        '#title' => t('Logo on the right side'),
        '#value' => theme('image', $logo_file->filepath, 'Header right logo.', $logo_file->filename),
      );
      $form['header']['h_right_logo_del'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete right logo.'),
      );
    }
    else {
      $form['header']['h_right_logo_file'] = array(
        '#type' => 'file',
        '#title' => t('Upload right logo'),
        '#size' => 60,
        '#maxlength' => 250,
        '#description' => t("Upload right side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $webform2pdf_default['h_right_logo_size'])),
      );
    }

    // PDF body (page)
    $form['page'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content of the PDF document'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $tokens = _webform2pdf_list_template_vars($node);
    array_unshift($tokens, '%pagebreak');

    $form['page']['p_body'] = array(
      '#type' => 'textarea',
      '#title' => t('Page body'),
      '#rows' => '10',
      '#default_value' => $default['p_body'],
      '#description' => t("The content of the PDF file can be defined here, the text can be formatted with HTML and CSS tags. The form elements can be referred with the following special strings: !vars. Select form elements can be outputted in different ways, write one of the following strings after the element name to choose from them: '-nl', '-all', '-nl-all'. '-nl ' modifier writes every selected element into a new line, '-all' lists every option, and marks which were selected from them. '-nl-all' lists all of the options in separate lines, and marks selected ones."
      , array('!vars' => implode(', ', $tokens ))) . theme('webform_token_help'),
    );

    $form['page']['format'] = filter_form($default['format']);

    $form['page']['p_txt_align'] = array(
      '#type' => 'select',
      '#title' => t('Text alignment'),
      '#default_value' => $default['p_txt_align'],
      '#options' => array(
        'L' => t('Align left'),
        'C' => t('Align center'),
        'R' => t('Align right'),
        ),
    );

    $form['page']['p_font_family'] = array(
      '#type' => 'select',
      '#title' => t('Font Family'),
      '#default_value' => $default['p_font_family'],
      '#options' => array(
        'helvetica' => 'Helvetica',
        'times' => 'Times',
        'courier' => 'Courier',
        'dejavusans' => 'Dejavu Sans',
        'dejavuserif' => 'Dejavu Serif',
        'freesans' => 'Free Sans',
        'freeserif' => 'Free Serif',
        'freemono' => 'Free Mono',
      ),
      '#description' => t('Set the font family to be used.'),
    );

    $form['page']['p_font_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Font Size'),
      '#default_value' => $default['p_font_size'],
      '#size' => 2,
      '#maxlength' => 3,
      '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
    );

    // Footer
    $form['footer'] = array(
      '#type' => 'fieldset',
      '#title' => t('PDF footer'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['footer']['f_left_logo'] = array(
      '#type' => 'value',
      '#value' => $default['f_left_logo'],
    );

    if ($default['f_left_logo']) {
      $logo_file = _webform2pdf_get_file($default['f_left_logo']);

      $form['footer']['f_left_logo_img'] = array(
        '#type' => 'item',
        '#title' => t('Logo on the left side'),
        '#value' => theme('image', $logo_file->filepath, 'Footer left logo.', $logo_file->filename),
      );
      $form['footer']['f_left_logo_del'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete left side logo.'),
      );
    }
    else {
      $form['footer']['f_left_logo_file'] = array(
        '#type' => 'file',
        '#title' => t('Upload left side logo'),
        '#size' => 60,
        '#maxlength' => 250,
        '#description' => t("Upload left side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $webform2pdf_default['f_left_logo_size'])),
      );
    }

    $form['footer']['f_txt'] = array(
      '#type' => 'textarea',
      '#title' => t('Footer text'),
      '#rows' => '2',
      '#default_value' => $default['f_txt'],
      '#resizable' => FALSE,
      '#description' => t("The PDF footer text. 2 rows maximum. The following special element can be used: %pagenumber - number of the page, %totalpage - total page count.") . theme('webform_token_help'),
    );

    $form['footer']['f_txt_align'] = array(
      '#type' => 'select',
      '#title' => t('Text alignment'),
      '#default_value' => $default['f_txt_align'],
      '#options' => array(
        'L' => t('Align left'),
        'C' => t('Align center'),
        'R' => t('Align right'),
      ),
    );

    $form['footer']['f_font_family'] = array(
      '#type' => 'select',
      '#title' => t('Font Family'),
      '#default_value' => $default['f_font_family'],
      '#options' => array(
        'helvetica' => 'Helvetica',
        'times' => 'Times',
        'courier' => 'Courier',
        'dejavusans' => 'Dejavu Sans',
        'dejavuserif' => 'Dejavu Serif',
        'freesans' => 'Free Sans',
        'freeserif' => 'Free Serif',
        'freemono' => 'Free Mono',
      ),
      '#description' => t('Set the font family to be used.'),
    );

    $form['footer']['f_font_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Font Size'),
      '#default_value' => $default['f_font_size'],
      '#size' => 2,
      '#maxlength' => 3,
      '#description' => t('Set the font size to be used for header text. This is the base value for the scaling applied to other text styles.'),
    );

    $form['footer']['f_right_logo'] = array(
      '#type' => 'value',
      '#value' => $default['f_right_logo'],
    );

    if ($default['f_right_logo']) {
      $logo_file = _webform2pdf_get_file($default['f_right_logo']);

      $form['footer']['f_right_logo_img'] = array(
        '#type' => 'item',
        '#title' => t('Logo on the right side'),
        '#value' => theme('image', $logo_file->filepath, 'Footer right logo.', $logo_file->filename),
      );
      $form['footer']['f_right_logo_del'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete right logo.'),
      );
    }
    else {
      $form['footer']['f_right_logo_file'] = array(
        '#type' => 'file',
        '#title' => t('Upload right logo'),
        '#size' => 60,
        '#maxlength' => 250,
        '#description' => t("Upload right side logo. If the size of the uploaded image is more than !size, it will be resized to this size.", array('!size' => $webform2pdf_default['f_right_logo_size'])),
      );
    }
  }
  else {
    // if 'Generate PDF' is not yet enabled
    $form['#submit'] = array('webform2pdf_enable_edit_form_submit');
  }

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  if ($default['enabled']) {
    $form['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    );
  }

  return $form;
} // function webform2pdf_edit_form()

/*
 * webform2pdf_edit_form_validate: implementation of validate hook
 */
function webform2pdf_edit_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Submit')) {
    $header = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['h_txt']) ) );

    if ( count($header) > 5) {
      form_set_error('h_txt', t('Up to 5 rows can be set!'));
    }

    $footer = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['f_txt']) ) );
    if ( count($footer) > 2) {
      form_set_error('f_txt', t('Up to 2 rows can be set!'));
    }
  }
} // function webform2pdf_edit_form_validate()

/*
 * webform2pdf_edit_form_submit: implementation of submit hook
 */
function webform2pdf_edit_form_submit($form, &$form_state) {
  $webform2pdf_default = variable_get('webform2pdf_default', '');

  if ($form_state['values']['op'] == t('Submit')) {
    $update['enabled'] = $form_state['values']['enabled'];
    $update['pdf_send_email'] = $form_state['values']['pdf_send_email'];
    $update['no_send_email_addr'] = serialize($form_state['values']['no_send_email_addr']);
    $update['page_format'] = $form_state['values']['page_format'];
    $update['page_orientation'] = $form_state['values']['page_orientation'];
    $update['h_left_logo'] = $form_state['values']['h_left_logo'];
    $update['h_right_logo'] = $form_state['values']['h_right_logo'];
    $update['f_left_logo'] = $form_state['values']['f_left_logo'];
    $update['f_right_logo'] = $form_state['values']['f_right_logo'];
    $update['h_font_size'] = $form_state['values']['h_font_size'];
    $update['p_font_size'] = $form_state['values']['p_font_size'];
    $update['f_font_size'] = $form_state['values']['f_font_size'];
    $update['h_txt_align'] = $form_state['values']['h_txt_align'];
    $update['h_font_family'] = $form_state['values']['h_font_family'];
    $update['p_txt_align'] = $form_state['values']['p_txt_align'];
    $update['p_font_family'] = $form_state['values']['p_font_family'];
    $update['f_txt_align'] = $form_state['values']['f_txt_align'];
    $update['f_font_family'] = $form_state['values']['f_font_family'];
    $update['h_txt'] = $form_state['values']['h_txt'];
    $update['f_txt'] = $form_state['values']['f_txt'];
    $update['p_body'] = $form_state['values']['p_body'];
    $update['format'] = $form_state['values']['format'];
    $update['nid'] = $form_state['values']['nid'];

    // Image file deleted.
    foreach (array('h_left_logo', 'h_right_logo', 'f_left_logo', 'f_right_logo') as $logo) {
      if ( isset($form_state['values'][$logo . '_del']) ) {
        if ( $form_state['values'][$logo . '_del'] ) {
          if ( (_webform2pdf_use_file($form_state['values'][$logo])-1) == 0) {
            $logo_file = _webform2pdf_get_file($form_state['values'][$logo]);
            file_delete($logo_file->filepath);
          }
          $update[$logo] = 0;
        }
      }
    }

    // Header and footer image file save.
    foreach (array('h_left_logo', 'h_right_logo', 'f_left_logo', 'f_right_logo') as $logo) {
      if ( isset($form_state['values'][$logo . '_file']) ) {
        $validators = array(
          'file_validate_is_image' => array(),
          'file_validate_image_resolution' => array($webform2pdf_default[$logo . '_size']),
        );

        if ( $file = file_save_upload($logo . '_file', $validators, file_directory_path() ) ) {
          file_set_status($file, FILE_STATUS_PERMANENT);
          $update[$logo] = $file->fid;
        }
      }
    }
  }
  elseif ($form_state['values']['op'] == t('Reset to defaults')) {
    $update['enabled'] = $form_state['values']['enabled'];
    $update['pdf_send_email'] = $webform2pdf_default['pdf_send_email'];
    $update['page_format'] = $webform2pdf_default['page_format'];
    $update['page_orientation'] = $webform2pdf_default['page_orientation'];
    $update['h_left_logo'] = $webform2pdf_default['h_left_logo'];
    $update['h_right_logo'] = $webform2pdf_default['h_right_logo'];
    $update['f_left_logo'] = $webform2pdf_default['f_left_logo'];
    $update['f_right_logo'] = $webform2pdf_default['f_right_logo'];
    $update['h_font_size'] = $webform2pdf_default['h_font_size'];
    $update['p_font_size'] = $webform2pdf_default['p_font_size'];
    $update['f_font_size'] = $webform2pdf_default['f_font_size'];
    $update['h_txt_align'] = $webform2pdf_default['h_txt_align'];
    $update['h_font_family'] = $webform2pdf_default['h_font_family'];
    $update['p_txt_align'] = $webform2pdf_default['p_txt_align'];
    $update['p_font_family'] = $webform2pdf_default['p_font_family'];
    $update['f_txt_align'] = $webform2pdf_default['f_txt_align'];
    $update['f_font_family'] = $webform2pdf_default['f_font_family'];
    $update['h_txt'] = $webform2pdf_default['h_txt'];
    $update['f_txt'] = $webform2pdf_default['f_txt'];
    $update['p_body'] = $webform2pdf_default['p_body'];
    $update['format'] = $webform2pdf_default['format'];
    $update['nid'] = $form_state['values']['nid'];

    // Image file deleted.
    foreach (array('h_left_logo', 'h_right_logo', 'f_left_logo', 'f_right_logo') as $logo) {
      if ( (_webform2pdf_use_file($form_state['values'][$logo])-1) == 0) {
        $logo_file = _webform2pdf_get_file($form_state['values'][$logo]);
        file_delete($logo_file->filepath);
      }
    }
  }

  // update settings
  $SQL = "UPDATE {webform2pdf} SET enabled = %d, pdf_send_email = %d, no_send_email_addr = '%s'";
  $SQL .= ", page_format = '%s', page_orientation = '%s', h_left_logo = %d, h_right_logo = %d";
  $SQL .= ", f_left_logo = %d, f_right_logo = %d, h_font_size = %d, p_font_size = %d";
  $SQL .= ", f_font_size = %d, h_txt_align = '%s', h_font_family = '%s'";
  $SQL .= ", p_txt_align = '%s', p_font_family = '%s', f_txt_align = '%s', f_font_family = '%s'";
  $SQL .= ", h_txt = '%s', f_txt = '%s', p_body = '%s', format = %d";
  $SQL .= " WHERE nid = %d";
  db_query($SQL, $update);
} // function webform2pdf_edit_form_submit()

/*
 * webform2pdf_enable_edit_form_submit: enables and saves advanced PDF generation settings for a webform
 */
function webform2pdf_enable_edit_form_submit($form, &$form_state) {
  if ($form_state['values']['enabled']) {
    $result = db_query("SELECT * FROM {webform2pdf} WHERE nid = %d", $form_state['values']['nid']);
    $row = db_fetch_array($result);
    if ($row['nid']) {
      $SQL = "UPDATE {webform2pdf} SET enabled = %d WHERE nid = %d";
      db_query($SQL, $form_state['values']['enabled'], $form_state['values']['nid']);
    }
    else {
      $default = variable_get('webform2pdf_default', '');
      unset($default['h_left_logo_size'], $default['h_right_logo_size'], $default['f_left_logo_size'], $default['f_right_logo_size']);

      $SQL = "INSERT INTO {webform2pdf} (nid, enabled, download, pdf_send_email, page_format, page_orientation,";
      $SQL .= " h_left_logo, h_right_logo, f_left_logo, f_right_logo, h_font_size, p_font_size, f_font_size,";
      $SQL .= " h_txt_align, h_font_family, p_txt_align, p_font_family, f_txt_align, f_font_family, h_txt,";
      $SQL .= " f_txt, p_body, format) VALUES (%d, %d, %d, %d, '%s', '%s', %d, %d, %d, %d,";
      $SQL .= " %d, %d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d)";
      db_query($SQL, $form_state['values']['nid'], $form_state['values']['enabled'], $default['download']
      , $default['pdf_send_email'], $default['page_format'], $default['page_orientation']
      , $default['h_left_logo'], $default['h_right_logo'], $default['f_left_logo'], $default['f_right_logo']
      , $default['h_font_size'], $default['p_font_size'], $default['f_font_size'], $default['h_txt_align']
      , $default['h_font_family'], $default['p_txt_align'], $default['p_font_family'], $default['f_txt_align']
      , $default['f_font_family'], $default['h_txt'], $default['f_txt'], $default['p_body'], $default['format']);
    }
  }
} // function webform2pdf_enable_edit_form_submit()

