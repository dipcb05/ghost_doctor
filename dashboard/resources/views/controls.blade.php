@extends('layouts.app')
@section('content')
<div class="row">
  <div class="col-10 d-flex justify-content-center text-center">
    <div class="card" style="width: 50rem;">
      <div class="card-header" style="text-align:center">Control</div>
        <div class="card-body">
            <div class="row">
             <table class="table table-bordered">
              <thead>
               <tr>
                  <th>Task Name</th>
                  <th>Status</th>
               </tr> 
              </thead>
              <tbody>
               @foreach($tasks as $t)
               @if($t['task_name'] != 'fan speed')
                  <tr>
                     <td>{{ $t['task_name'] }}</td>
                     <td>
                       <input data-name="{{$t['task_name']}}" 
                              class="toggle-class" 
                              type="checkbox" 
                              data-onstyle="success" 
                              data-offstyle="danger" 
                              data-toggle="toggle" 
                              data-on="On" 
                              data-off="Off"
                              {{ $t['task_value'] ? 'checked' : '' }}>
                     </td>
                  </tr>
                @endif
               @endforeach
            
             </tbody>
             </table>
            </div>  
            <div class = "row">
              <div>
              <span>Fan Speed</span>
              <input type="range" min="1" max="100" value="{{ $tasks[3]['task_value']}}" id="fan_speed">
              <p>Value: <span id="speed_value"></span></p>
              </div>
            </div>
        </div>
      </div>
    </div>
  </div>
</div>

<script>
  var slider = document.getElementById("fan_speed");
  var output = document.getElementById("speed_value");
  output.innerHTML = slider.value;
  slider.oninput = function() {
  output.innerHTML = this.value;
  }
  slider.onchange = function(){
    $.ajax({
            type: "GET",
            dataType: "json",
            url: '/changeStatus',
            data: {'value': slider.value, 'task_name': "fan_speed"},
            success: function(data){
              console.log(data.success)
            }
    });
  }
  $(function() {
    $('.toggle-class').change(function() {
        var status = $(this).prop('checked') == true ? 1 : 0; 
        var task_name = $(this).data('name'); 
        $.ajax({
            type: "GET",
            dataType: "json",
            url: '/changeStatus',
            data: {'status': status, 'task_name': task_name},
            success: function(data){
              console.log(data.success)
            }
        });
    })
  })
</script>
@endsection