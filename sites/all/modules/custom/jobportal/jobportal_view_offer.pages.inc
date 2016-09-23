<?php

function jobportal_view_offer_page() {
	
	$content = "";
	$content['raw-markup'] = array(
		'#type' => 'markup',
		'#markup' => '',
	);
	
	if(isset($_GET['oid'])) {
		
		$oid = $_GET['oid'];
		$offer = load_offer_from_database($oid);
		$company = $offer['company'];
		$country = $offer['country'];
		$title = $offer['title'];
		$about = $offer['about'];
		$position_n = $offer['positions_n'];
		$created = gmdate("d/m/Y", $offer['created']);
		
		$apply_link_html = "";
		global $user;
		if ( in_array ('employer' , $user->roles)) {
			$href = url('offers/' . $oid . '/apply');
			$apply_link_html = "
			<a href='$href' style='text-decoration:none;'>
				<button style='width:50%; height:36px; display:block;margin-top:25px;'>
					Apply
				</button>
			</a>";
		}
		
			
		if ($offer) {
			$content['raw-markup']['#markup'] .= "
			<div style='font-family:Roboto!important;'>
				<div style='display:inline-block; width:350px;'>
					<h2 style='font-size:22px;'>Company</h2>
					<span style='color:#000000;font-family:Arial;font-size:15px;'>$company</span>
				</div>
				<div style='display:inline-block;'>
					<h2 style='font-size:22px;'>Country</h2>
					<span style='color:#000000;font-family:Arial;font-size:15px;'>$country</span>
				</div>
			</div>
			<div style='clear:both;'></div>
			<h2 style='font-size:26px;'>$title</h2>
			<span style='color:#000000;font-family:Arial;font-size:16px;'>$about</span>
			
			<h4>Created:<span style='color:#000000;font-family:Arial;font-size:13px;'> $created</span></h4>
			<h4>Number of Positions: <span style='color:#000000;font-family:Arial;font-size:13px;'> $position_n</span></h4>
			
			$apply_link_html
			";			
			return $content;
		}
	} 
	
	$content['raw-markup']['#markup'] .= "<h1>This offer could not be found.</h1>";
	return $content;
}

function load_offer_from_database($oid) {
	
	$query_result = db_select('jobportal_offer', 'n')
		->fields('n')
		->condition('oid', $oid)
		->execute()
		->fetchAssoc();
	
	return $query_result;
}

