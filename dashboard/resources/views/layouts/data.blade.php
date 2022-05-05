@extends('layouts.app')
@section('content')
<br><br>
<div class="row">
    <div class="col-10 d-flex justify-content-center text-center">
     <div class="card" style="width: 50rem;">
      <div class="card-header" style="text-align:center">All Data</div>
      <div class="card-body">
          <table class="table">
          <thead>
           <tr>
            <th scope="col" style="text-align:center">#</th>
            <th scope="col" style="text-align:center">Datetime</th>
            <th scope="col" style="text-align:center">Humidity Condition</th>
            <th scope="col" style="text-align:center">Temparature</th>
           </tr>
          </thead>
          <tbody>
           @php($i = 0)
           @foreach(array_reverse($posts) as $post)
           @php($i++)
            <tr>
             <td style="text-align:center"><h6>{{ $i }}</h6></td>
             <td style="text-align:center"><h7>{{ $post['datetime'] }}</h7></td>
             <td style="text-align:center"><h6>{{ $post['humidity'] }}%</h6></td>
             <td style="text-align:center"><h6>{{ $post['temparature'] }}°</h6></td>
            </tr>
            @endforeach
          </tbody>
         </table>
        </div>
    </div>
</div>
</div>
@endsection