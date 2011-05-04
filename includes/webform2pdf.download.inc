<?php
/*
 * webform2pdf_submission_download_pdf: download submission as one PDF file
 */
function webform2pdf_submission_download_pdf($node, $submission, $output_type = 'I') {
  $output_types = array('I', 'D', 'S');

  if ( in_array($output_type, $output_types) ) {
    $tokens = _webform2pdf_get_template_vars($node, $submission);
    $template = _webform2pdf_get_template($node->nid);

    $pdf = theme('webform2pdf_pdf_init', $node, $template);
    if ( !empty($pdf) ) {
      $pdf = theme('webform2pdf_pdf_header', $pdf, $node, $template);
      $pdf = theme('webform2pdf_pdf_footer', $pdf, $node, $template);
      $pdf = theme('webform2pdf_pdf_page', $pdf);

      // initialize document
      $pdf->AliasNbPages();

      $template['pages'] = explode('%pagebreak', $template['p_body']);

      foreach ($template['pages'] as $key => $page) {
        $template['pages'][$key] = strtr($page, $tokens);
      }

      $pdf = theme('webform2pdf_pdf_content', $pdf, $node, $template, $tokens);

      // reset pointer to the last page
      $pdf->lastPage();

      $filename = theme('webform2pdf_filename', $node, $submission);

      if ( $output_type == 'S') {
        return $pdf->Output($filename, $output_type);
      }
      else {
        // Close and output PDF document
        $pdf->Output($filename, $output_type);
        die;
      }
    }
  }
} // function webform2pdf_submission_download_pdf()

/*
 * _webform2pdf_download_pdf_form: Creates a form, where the submissions can be downloaded in PDF format
 */
function webform2pdf_download_pdf_form(&$form_state, $node) {
  module_load_include('inc', 'webform', 'webform.report');
  $header = theme('webform_results_submissions_header', $node);
  $submissions = webform_get_submissions($node->nid, $header);

  $form = $options = array();
  foreach ($submissions as $sid => $submission) {
    $form['sid'][$sid] = array('#value' => $sid);
    $form['date'][$sid] = array('#value' => format_date($submission->submitted, 'small'));
    $form['username'][$sid] = array('#value' => theme('username', $submission));
    $form['remote_addr'][$sid] = array('#value' => $submission->remote_addr);
    $form['view'][$sid] = array('#value' => l(t('View'), "node/$node->nid/submission/$sid"));
    $form['download_pdf'][$sid] = array('#value' => l(t('Download PDF'), "node/$node->nid/submission/$sid/downloadpdf"));
    $options[$sid] = '';
  }

  $form['sids'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
  );

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Download PDF'),
  );

  return $form;
} // function webform2pdf_download_pdf_form()

/*
 * theme_webform2pdf_download_pdf_form: webform2pdf_download_pdf_form of theme hook
 */
function theme_webform2pdf_download_pdf_form($form) {
  $output = '';
  $header = theme('webform_results_submissions_header', $node);
  $hc = theme('table_select_header_cell');
  array_unshift($header, $hc );
  $rows = array();
  foreach ($form['sids']['#options'] as $sid => $empty) {
    $row = array();
    $row[] = array('data' => drupal_render($form['sids'][$sid]), 'class' => 'checkbox' );
    $row[] = array('data' => drupal_render($form['sid'][$sid]) );
    $row[] = array('data' => drupal_render($form['date'][$sid]) );
    $row[] = array('data' => drupal_render($form['username'][$sid]) );
    $row[] = array('data' => drupal_render($form['remote_addr'][$sid]) );
    $row[] = array('data' => drupal_render($form['view'][$sid]) );
    $row[] = array('data' => drupal_render($form['download_pdf'][$sid]) );
    $rows[] = $row;
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
} // function theme_webform2pdf_download_pdf_form()

/*
 * webform2pdf_download_pdf_form_submit: webform2pdf_download_pdf_form of submit hook
 */
function webform2pdf_download_pdf_form_submit($form, &$form_state) {
  // filter zero values
  $form_state['values']['sids'] = array_filter($form_state['values']['sids']);

  // If there is a selected form element
  if (count($form_state['values']['sids'])) {
    // call header generator
    $header = theme('webform_results_submissions_header', $node);

    $submissions = _webform2pdf_get_submissions($form_state['values']['nid'], $header, $form_state['values']['sids']);
    $node = node_load($form_state['values']['nid']);
    $template = _webform2pdf_get_template($node->nid);

    $tokens = array();
    foreach ($submissions as $key => $submission) {
      $tokens[$key] = _webform2pdf_get_template_vars($node, $submission);
    }

    $pdf = theme('webform2pdf_pdf_init', $node, $template);
    $pdf = theme('webform2pdf_pdf_header', $pdf, $node, $template);
    $pdf = theme('webform2pdf_pdf_footer', $pdf, $node, $template);
    $pdf = theme('webform2pdf_pdf_page', $pdf);

    // initialize document
    $pdf->AliasNbPages();

    // Inserts every token value into the template
    foreach ($tokens as $key => $token) {
      $pages[$key] = strtr($template['p_body'], $token);
    }

    $template['pages'] = implode('%pagebreak', $pages);
    $template['pages'] = explode('%pagebreak', $template['pages']);

    $pdf = theme('webform2pdf_pdf_content', $pdf, $node, $template, $tokens);

    // reset pointer to the last page
    $pdf->lastPage();
    $filename = theme('webform2pdf_filename', $node, time());

    // Close and output PDF document
    $pdf->Output($filename, 'I');
    die;
  }
} // function webform2pdf_download_pdf_form_submit()

/*
 * webform2pdf_url_encode: pdf download anonymous url generation.
 */
function webform2pdf_url_decode($url) {
  if ( function_exists('mcrypt_decrypt')  ) {
    $key = variable_get('webform2pdf_key', '');
    $url2 = trim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $key, urldecode(base64_decode($url)), MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND)));

    list($tmp, $nid, $tmp, $sid, $tmp) = explode('/', $url2);
    unset($tmp, $url2);
    if ( is_int($nid) && is_int($sid) ) {
      $node = webform_menu_load($nid);
      $submission = webform_menu_submission_load($sid, $nid);
      if ( !empty($node) && !empty($submission) ) {
        return webform2pdf_submission_download_pdf($node, $submission);
      }
    }
  }
  drupal_not_found();
} // function webform2pdf_url_encode()
