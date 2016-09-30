<?php

function jobportal_apply_form($form,  &$form_state) {
	
	global $user;
	if (!in_array ('employee', $user->roles) ) {
		drupal_access_denied();
		return NULL;
	}
	
	if(!isset($_GET['oid'])) {
		drupal_not_found();
		return NULL;
	}
	
	$form = array();
	
	if (applicationsExists() == false) {
		$form['apply_message'] = array(
			'#type' => 'textarea',
			'#title' => t('Application Message'),
			'#maxlength' => '255',
		);
		$form['submit_button'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
		);
	} else {
		drupal_set_message(t('You are already applied to this job!'));
	}
	
	return $form;
}

function jobportal_apply_form_submit($form,  &$form_state) {
	global $user;
	
	$oid = $_GET['oid'];
	$uid = $user->uid;
	$message = $form_state['values']['apply_message'];
	
	$table_name = 'jobportal_applicants';
	
	$insert = db_insert($table_name)
				->fields(array(
					'aid' => NULL,
					'oid' => $oid,
					'uid' => $uid,
					'message' => $message,
					'created' => REQUEST_TIME,
					))
				->execute();
				
	//drupal_set_message(t('You applied Sucessfully!'));
}

function applicationsExists() {
	global $user;
	$uid = $user->uid;
	$oid = $_GET['oid'];
	
	$result = array();
	$query_result = db_select('jobportal_applicants', 'n')
		->fields('n')
		->condition('uid', $uid,'=')
		->condition('oid', $oid,'=')
		->execute();
	
	$result = $query_result->fetchAssoc();
	return $result;
}
