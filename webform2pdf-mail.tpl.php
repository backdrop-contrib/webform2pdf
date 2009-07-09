<?php
global $webform2pdf_send2pdf;

$webform2pdf = _webform2pdf_get_template($node->nid);
if ($webform2pdf['enabled']) {
  // Check for a multi-page form that is not yet complete.
  $webform2pdf_send2pdf = array('nid' => $node->nid, 'sid' => $sid);
}
