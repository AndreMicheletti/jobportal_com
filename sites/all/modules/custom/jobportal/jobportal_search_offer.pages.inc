<?php

function jobportal_search_offer_page($page) {
	
	$content['raw-markup'] = array(
		'#type' => 'markup',
		'#markup' => '',
	);
	
	$offersArray = load_from_database($page);
	
	foreach ($offersArray as $offer) {
		$content['raw-markup']['#markup'] .= offer_table_markup(
			$offer['oid'],
			$offer['company'],
			$offer['country'],
			$offer['title'],
			$offer['about'],
			$offer['positions_n']
		);
	}
	$next_page = $page + 1;
	$content['raw-markup']['#markup'] .= 
	t('<a href="@url">Next Page</a>', array('@url' => url("offers/search?page=$next_page")));
	
	return $content;
	
}

function load_from_database($page, $limit = 10) {
	$start = ($limit * $page) + 1;
	$end = $limit * ($page + 1);
	
	$result = array();
	$query_result = db_select('jobportal_offer', 'n')
		->fields('n')
		->orderBy('created', 'DESC')
		->range($start, $end)
		->execute();
	
	while ($x = $query_result->fetchAssoc()) {
		array_push($result, $x);
	}
	
	return $result;
}

function offer_table_markup($oid, $company, $country, $title, $about, $positions_n) {
	
	$href = ''; // TO IMPLEMENT
	return "
		<table style='width:503px;height:213px;'>
		<tr>
		<td colspan='3' class='cell0'><span style='color:#000000;font-family:Verdana;font-size:21px;line-height:22px;'>$title</span></td>
		</tr>
		<tr>
		<td class='cell1'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'> Company</span></td>
		<td colspan='2' class='cell2'><span style='color:#000000;font-family:Arial;font-size:13px;line-height:16px;'>$company</span></td>
		</tr>
		<tr>
		<td class='cell3'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'> Country</span></td>
		<td colspan='2' class='cell4'><span style='color:#000000;font-family:Arial;font-size:13px;line-height:16px;'>$country</span></td>
		</tr>
		<tr>
		<td colspan='3' class='cell5'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>About:<br><br></span><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>$about</span>
		</tr>
		<tr>
		<td class='cell6'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>Number of Positions</span></td>
		<td class='cell7'><span style='color:#000000;font-family:Verdana;font-size:15px;line-height:17px;'>$positions_n</span></td>
		<td class='cell0'><span style='color:#000000;font-family:Arial;font-size:13px;line-height:16px;'>
			<a href='$href'><button style='width:100%; height:30px; border-radius:0px;'>Apply</button></a>
		</span></td>
		</tr>
		</table><br>
	";
}
