<?php

function jobportal_search_offer_page($page) {
	
	$page = (isset($_GET['page']) ? $_GET['page'] : $page);
	$limit_per_page = 10;
	
	$content['raw-markup'] = array(
		'#type' => 'markup',
		'#markup' => '',
	);
	
	$offersArray = load_from_database($page, $limit_per_page);
	
	$i = 0;
	foreach ($offersArray as $offer) {
		if ($i == $limit_per_page) break;
		$content['raw-markup']['#markup'] .= offer_table_markup(
			$offer['oid'],
			$offer['company'],
			$offer['country'],
			$offer['title'],
			$offer['about'],
			$offer['positions_n']
		);
		$i++;
	}
	
	if (count($offersArray) > $limit_per_page) {
		$next_page = $page + 1;
		$content['raw-markup']['#markup'] .= ("<a href='search?page=$next_page'>Next Page</a>");
	}
	
	return $content;
	
}

function load_from_database($page, $limit = 10) {
	$start = ($limit * $page);
	$end = ($limit * ($page + 1)) + 1;
	
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
	//$details_href = url("offers/$oid/details");
	$details_href = ("view?oid=$oid");
	$result = "
	<style>
		tr, td { background-color:#FFF; }
		a.offer:hover {text-decoration:none;}
		a.offer:visited {color:black;text-decoration:none;}
	</style>
	<a class='offer' href='$details_href'>
		<table style='width:503px;height:153px;background-color:#FFF;'>
		<tr>
		<td colspan='3' class='cell0'><span style='color:#000000;font-family:Verdana;font-size:21px;line-height:22px;'>
			<a href='$details_href'>$title</a>
		</span></td>
		</tr>
		<tr>
		<td class='cell1'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'> Company</span></td>
		<td colspan='2' class='cell2'><span style='color:#000000;font-family:Arial;font-size:14px;line-height:16px;'>$company</span></td>
		</tr>
		<tr>
		<td class='cell3'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'> Country</span></td>
		<td colspan='2' class='cell4'><span style='color:#000000;font-family:Arial;font-size:14px;line-height:16px;'>$country</span></td>
		</tr>
		<!--
			<tr>
			<td colspan='3' class='cell5'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>About:<br><br></span><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>$about</span>
			</tr>
		-->
		<tr>
		<td class='cell6'><span style='color:#000000;font-family:Verdana;font-size:16px;line-height:18px;'>Number of Positions</span></td>
		<td class='cell7'><span style='color:#000000;font-family:Verdana;font-size:15px;line-height:17px;'>$positions_n</span></td>
		<td class='cell0'><span style='color:#000000;font-family:Arial;font-size:13px;line-height:16px;'>
		";
		
	global $user;
	if (in_array ('employee', $user->roles) ) {
		$result .= "<a href='" . url("offers/$oid/apply") . "'><button style='width:100%; height:30px; border-radius:0px;'>Apply</button></a>";
	}
	
	$result .= "
		</span></td>
		</tr>
		</table>
	</a><br>";

	return $result;
}
