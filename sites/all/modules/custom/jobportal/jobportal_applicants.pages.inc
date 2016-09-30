<?php

function jobportal_applicants_page() {
	
	global $user;
	if (!in_array ('employer', $user->roles) ) {
		drupal_access_denied();
		return NULL;
	}

	if (isset($_GET['oid'])) {
		$oid = $_GET['oid'];
	} else {
		drupal_not_found();
		return NULL;
	}
	
	$content['raw-markup'] = array(
		'#type' => 'markup',
		'#markup' => '',
	);
	
	$result = load_from_database($oid);
	
	$i = 0;
	foreach ($result as $applicant) {
		$content['raw-markup']['#markup'] .= applicant_table_markup(
			$applicant['uid'],
			$applicant['message']
		);
		$i++;
	}
	
	return $content;
}

function load_from_database($oid) {	
	$result = array();
	$query_result = db_select('jobportal_applicants', 'n')
		->fields('n')
		->condition('oid', $oid,'=')
		->orderBy('created', 'DESC')
		->execute();
	
	while ($x = $query_result->fetchAssoc()) {
		array_push($result, $x);
	}
	
	return $result;
}

function applicant_table_markup($uid,$message) {
	$result = "
	<style>
		tr, td { background-color:#FFF; }
		a.offer:hover {text-decoration:none;}
		a.offer:visited {color:black;text-decoration:none;}
	</style>
	<table style='width:503px;height:153px;background-color:#FFF;'>
	<tr>	 
		<td class='cell6'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>User ID: $uid</span></td>
	</tr>
	<tr>
		<td colspan='3' class='cell5'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:10px;'>Message:<br><br></span><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:10px;'>$message</span>
	</tr>
	<tr>
	</tr>
	</table>
	<hr>
	<br>
	";

	return $result;
}
