<?php

function jobportal_add_offer() {
	$content['raw-markup'] = array(
		'#type' => 'markup',
		'#markup' => '<p>Hello World!</p>',
	);
	return $content;
}

function jobportal_add_offer_form($form,  &$form_state) {
	
	$form['job_company'] = array(
		'#type' => 'textfield',
		'#title' => 'Company',
		'#maxlength' => '25',
		'#required' => TRUE,
	);
	$form['job_place'] = array(
		'#type' => 'textfield',
		'#title' => 'Country',
		'#maxlength' => '25',
		'#required' => TRUE,	
	);
	$form['job_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Headline'),
		'#maxlength' => '25',
		'#required' => TRUE,	
	  );
	  $form['job_about'] = array(
		'#type' => 'textarea',
		'#title' => t('About'),
		'#maxlength' => '255',
	  );
	  $form['job_positions'] = array(
		'#type' => 'textfield',
		'#title' => t('Number of Positions'),
		'#default_value' => 1,
		//'#description' => t('Number of positions available for this offer'),
		'#size' => 10,
		'#maxlength' => '2',	
		'#required' => TRUE,
	  );
	  $form['submit_button'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	  );
	  
	  return $form;
}

function jobportal_add_offer_form_validate($form,  &$form_state) {
	if (intval($form_state['values']['job_positions']) <= 0){
		form_set_error('job_positions', t('Number of Positions must be greater than 0'));
	}
}

function jobportal_add_offer_form_submit($form,  &$form_state) {
	global $user;
	
	$uid = $user->uid;
	$company = $form_state['values']['job_company'];
	$country = $form_state['values']['job_place'];
	$title = $form_state['values']['job_title'];
	$about = $form_state['values']['job_about'];
	$positions_n = intval($form_state['values']['job_positions']);
	
	$table_name = 'jobportal_offer';
	
	$insert = db_insert($table_name)
				->fields(array(
					'oid' => NULL,
					'uid' => $uid,
					'company' => $company,
					'country' => $country,
					'title' => $title,
					'about' => $about,
					'positions_n' => $positions_n,
					'created' => REQUEST_TIME,
					))
				->execute();
				
	drupal_set_message(t('Job offer was created sucessfully!'));
}
