<?php

/**
 * @file
 * Views hooks implemented for the Webform2pdf module.
 */

/**
 * Implements hook_views_data_alter().
 */
function webform2pdf_views_data_alter(&$data) {
  // View submission link.
  $data['webform_submissions']['download_pdf'] = array(
    'title' => t('Download PDF'),
    'help' => t('Provide a simple link to pdf.'),
    'real field' => 'serial',
    'field' => array(
      'handler' => 'webform2pdf_handler_field_submission_download_pdf',
      'click sortable' => TRUE,
      'real field' => 'sid',
      'link_type' => 'download pdf',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
}

/**
 * Implements hook_views_pre_view().
 *
 * Add the "download pdf" operation to the list of webform submissions.
 */
function webform2pdf_views_pre_view(&$view, &$display_id, &$args) {

  // The D7 module implemented hook_views_default_views_alter() to add the
  // download pdf link automatically to a webform's list of submissions. We can
  // no longer alter default views (because they're in config files), but this
  // code automatically adds it to the webform_submissions View, but only for
  // webforms for which we checked "Generate PDF document".
  if ($view->name == 'webform_submissions') {

    $nid = $args[0];
    $pdf_settings = webform2pdf_get_setting($nid);
    if (empty($pdf_settings) || !$pdf_settings['enabled']) {
      return;
    }

    // Generate PDF was enabled, so add an extra link to the PDF download.
    $download_pdf = array(
      'id' => 'download_pdf',
      'table' => 'webform_submissions',
      'field' => 'download_pdf',
      'label' => '',
      'element_label_colon' => FALSE,
      'access_check' => 0,
    );
    $view->display_handler->options['fields']['download_pdf'] = $download_pdf;
    $view->display_handler->options['style_options']['columns']['download_pdf'] = 'view_submission_1';
  }
}
